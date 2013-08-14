#include "stdafx.h"
#include "trace.h"
#include "Plug.h"
#include "Subcls.h"
#include "llcom.h"

HDC (WINAPI* stub_GetDC)( HWND ) = ::GetDC;
int (WINAPI* stub_ReleaseDC)( HWND, HDC ) = ::ReleaseDC;
BOOL (WINAPI* stub_BitBlt)( HDC, int, int, int, int, HDC, int, int, DWORD ) = ::BitBlt;
BOOL (WINAPI* stub_UpdateLayeredWindow)( HWND, HDC, POINT*, SIZE*, HDC, POINT*, COLORREF, BLENDFUNCTION*, DWORD ) = ::UpdateLayeredWindow;
LRESULT (WINAPI* stub_DispatchMessage)( const MSG* ) = ::DispatchMessage;
HRESULT (WINAPI* stub_CreateDXGIFactory1)( REFIID riid, void **ppFactory ) = ::CreateDXGIFactory1;
HRESULT (WINAPI* stub_CreateDXGIFactory)( REFIID riid, void **ppFactory ) = ::CreateDXGIFactory;

// "CDXGIFactory::CreateSwapChainImpl"
type_CreateSwapChain stub_CreateSwapChain;
type_CreateSwapChainForHwnd stub_CreateSwapChainForHwnd;
type_Present stub_Present;
type_Present1 stub_Present1;
type_EndDraw stub_EndDraw;


HDC WINAPI my_GetDC( HWND hwnd )
{
	log_frame( "user", u::info ) << log_var(hwnd) << u::endh;

	HDC hdc = (*stub_GetDC)( hwnd );

	frame << log_ret(hdc);
	return hdc;
}

int WINAPI my_ReleaseDC( HWND hwnd, HDC hdc )
{
	log_frame( "user", u::info ) << log_var(hwnd) << log_var(hdc) << u::endh;

	int result = (*stub_ReleaseDC)( hwnd, hdc );

	frame << log_ret(result);
	return result;
}

int WINAPI my_BitBlt( HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop )
{
	log_frame( "gdi", u::info ) << log_var(hdc) << log_var(x) << log_var(y) << log_var(cx) << log_var(cy) << log_var(rop) << u::endh;

	BOOL result = (*stub_BitBlt)( hdc, x, y, cx, cy, hdcSrc, x1, y1, rop );

	frame << log_ret(result);
	return result;

}



BOOL WINAPI my_UpdateLayeredWindow( HWND hwnd, HDC hdcDst, POINT *pptDst, SIZE *psize, HDC hdcSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags )
{
	log_frame( "gdi", u::info ) << log_var(hwnd) << u::endh;
	BOOL result = (*stub_UpdateLayeredWindow)( hwnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags );
	frame << log_ret(result);
	return result;
}


LRESULT WINAPI my_DispatchMessage( const MSG *pmsg )
{
	log_frame( "user", u::info ) << log_var(pmsg->hwnd) << log_var_f(pmsg->message, "%x") << u::endh;
	LRESULT result = (*stub_DispatchMessage)(pmsg);

	if( pmsg->message == 0x401 ) {
		CPlug* pplug = CPlug::inst();
		if( pplug ) {
			CSubclsWnd* pwnd = pplug->getSubclsWnd();
			if( pwnd ) {
		        //CPlug::inst()->getSubclsWnd()->highlight();
			}
		}
	}

	frame << log_ret(result);
	return result; 
}

HRESULT WINAPI my_CreateDXGIFactory1( REFIID riid, void **ppFactory )
{
	log_frame( "dxgi", u::info ) << u::endh;
	HRESULT result = (*stub_CreateDXGIFactory1)(riid, ppFactory);
	frame << log_ret(result);
	return result;
}

HRESULT WINAPI my_CreateDXGIFactory( REFIID riid, void** ppFactory )
{
	log_frame( "dxgi", u::info ) << u::endh;
	HRESULT result = (*stub_CreateDXGIFactory)(riid, ppFactory);
	frame << log_ret(result);
	return result;
}


HRESULT STDMETHODCALLTYPE my_CreateSwapChain( IDXGIFactory* This, IUnknown* ifDevice, DXGI_SWAP_CHAIN_DESC* pdesc, IDXGISwapChain** ppSwapChain )
{
	log_frame( "dxgi", u::info ) << log_var(ifDevice) << log_var(pdesc->OutputWindow) << log_var(pdesc->BufferCount) <<
		log_var(pdesc->BufferDesc.Width) << log_var(pdesc->BufferDesc.Height) << u::endh;
	HRESULT result = (*stub_CreateSwapChain)( This, ifDevice, pdesc, ppSwapChain );
	frame << log_ret(result);
	return result;
}


HRESULT STDMETHODCALLTYPE my_CreateSwapChainForHwnd( IDXGIFactory2* This, IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, 
	const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain )
{
	log_frame( "dxgi", u::info ) << log_var(pDevice) << log_var(hWnd) << 
		log_var(pDesc->Width) << log_var(pDesc->Height) << log_var(pDesc->BufferCount) << u::endh;
	HRESULT result = (*stub_CreateSwapChainForHwnd)( This, pDevice, hWnd, pDesc, pFullscreenDesc, pRestrictToOutput, ppSwapChain );
	frame << log_var(*ppSwapChain) << log_ret(result);
	return result;
}


HRESULT STDMETHODCALLTYPE my_Present( IDXGISwapChain* This, UINT SyncInterval, UINT Flags )
{
	log_frame( "dxgi", u::info ) << log_var(This) << u::endh;
	HRESULT result = (*stub_Present)(This, SyncInterval, Flags );
	frame << log_ret(result);
	return result;
}

HRESULT STDMETHODCALLTYPE my_Present1( IDXGISwapChain1* This, UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters )
{
	log_frame( "dxgi", u::info ) << log_var(This) << u::endh;
	HRESULT result = (*stub_Present1)(This, SyncInterval, PresentFlags, pPresentParameters );
	frame << log_ret(result);
	return result;
}


HRESULT STDMETHODCALLTYPE my_EndDraw( ID2D1RenderTarget* This, D2D1_TAG *tag1, D2D1_TAG *tag2 )
{
	HRESULT hr;
	log_frame( "d2d1", u::info ) << log_var(This) << u::endh;


	CComPtr<ID2D1SolidColorBrush> ifBrush;

	hr = This->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::AliceBlue ), &ifBrush );
	
	This->DrawLine( D2D1::Point2F(0.0f, 0.0f), D2D1::Point2F(480.0f, 480.0f), ifBrush );

	HRESULT result = (*stub_EndDraw)(This, tag1, tag2 );
	frame << log_ret(result);
	return result;
}



// ----------------------------------------
#define hook(fn)      { &(void*&)stub_##fn, my_##fn }

struct HookRecord {
	void** ptr;
	void* detour;
} g_hooks[] = {
	//hook(GetDC),
	//hook(ReleaseDC),
	//hook(BitBlt),
	//hook(UpdateLayeredWindow),
	//hook(DispatchMessage),
	//hook(CreateDXGIFactory1),
	//hook(CreateDXGIFactory),
	hook(CreateSwapChain),
	hook(CreateSwapChainForHwnd),
	hook(Present),
	hook(Present1),
	hook(EndDraw),
};

void resolveAddresses()
{
	/* use this method as an alternative to dbghelp. For now we are good without it.
	HRESULT hr = S_OK;
	CComPtr<IDXGIFactory> dxgiFactory;
	CComPtr<IDXGIFactory2> dxgiFactory2;

	hr = CreateDXGIFactory( __uuidof(IDXGIFactory), (void**)&dxgiFactory );
	if( SUCCEEDED(hr) ) {
		stub_CreateSwapChain = resolve_CreateSwapChain( dxgiFactory );
	}

	hr = dxgiFactory.QueryInterface( &dxgiFactory2 );
	if( SUCCEEDED(hr) ) {
		stub_CreateSwapChainForHwnd = resolve_CreateSwapChainForHwnd( dxgiFactory2 );
	}
	*/

	stub_CreateSwapChain = static_cast<type_CreateSwapChain>( DetourFindFunction( "dxgi.dll", symbol_CreateSwapChain ) );
	stub_CreateSwapChainForHwnd = static_cast<type_CreateSwapChainForHwnd>(	DetourFindFunction( "dxgi.dll", symbol_CreateSwapChainForHwnd ) );
	stub_Present = static_cast<type_Present>( DetourFindFunction( "dxgi.dll", symbol_Present ) );
	stub_Present1 = static_cast<type_Present1>( DetourFindFunction( "dxgi.dll", symbol_Present1 ) );
	stub_EndDraw = static_cast<type_EndDraw>( DetourFindFunction( "d2d1.dll", symbol_EndDraw ) );
}

void attachDetours( )
{
	LONG result, result1;

	resolveAddresses();

    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread() );
	for( HookRecord& h : g_hooks ) {
		result1 = DetourAttach( h.ptr, h.detour );
	};
    result = DetourTransactionCommit( );
}


void detachDetours( )
{
    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread() );
	for( HookRecord& h : g_hooks ) {
	    DetourDetach( h.ptr, h.detour );
	}
    DetourTransactionCommit( );
}
