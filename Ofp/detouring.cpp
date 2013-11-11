#include "stdafx.h"
#include "trace.h"
#include "Plug.h"
#include "Subcls.h"
#include "llcom.h"

extern long g_markLeft, g_markTop, g_markWidth, g_markHeight;
extern POINT g_ptMark;
extern bool g_fRosebud;

ID2D1RenderTarget* g_ifCurrentDrawTransaction = NULL;
bool g_fHadGlyph = false;


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
type_Present stub_Present_1;
type_Present stub_Present_2;
type_Present1 stub_Present1;
type_BeginDraw stub_BeginDraw;
type_EndDraw stub_EndDraw_1;
type_EndDraw stub_EndDraw_2;
type_EndDraw stub_EndDraw_3;
type_EndDraw stub_EndDraw_4;
type_EndDraw stub_EndDraw_5;
type_CreateWicBitmapRenderTarget stub_CreateWicBitmapRenderTarget;
type_DrawGlyphRun stub_DrawGlyphRun;
type_CreateBitmapFromWicBitmap stub_CreateBitmapFromWicBitmap;
type_DrawBitmap stub_DrawBitmap;

struct tr_Present_1 {
	static char const* const symbol() { return symbol_Present_1; }
	static type_Present& stub() { return stub_Present_1; }
};
struct tr_Present_2 {
	static char const* const symbol() { return symbol_Present_2; }
	static type_Present& stub() { return stub_Present_2; }
};

struct tr_EndDraw_1 {
	static char const* const symbol() { return symbol_EndDraw_1; }
	static type_EndDraw& stub() { return stub_EndDraw_1; }
	static char const* const name() { return "EndDraw_1"; }
};
struct tr_EndDraw_2 {
	static char const* const symbol() { return symbol_EndDraw_2; }
	static type_EndDraw& stub() { return stub_EndDraw_2; }
	static char const* const name() { return "EndDraw_2"; }
};
struct tr_EndDraw_3 {
	static char const* const symbol() { return symbol_EndDraw_3; }
	static type_EndDraw& stub() { return stub_EndDraw_3; }
	static char const* const name() { return "EndDraw_3"; }
};
struct tr_EndDraw_4 {
	static char const* const symbol() { return symbol_EndDraw_4; }
	static type_EndDraw& stub() { return stub_EndDraw_4; }
	static char const* const name() { return "EndDraw_4"; }
};
struct tr_EndDraw_5 {
	static char const* const symbol() { return symbol_EndDraw_5; }
	static type_EndDraw& stub() { return stub_EndDraw_5; }
	static char const* const name() { return "EndDraw_5"; }
};




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

template< typename Tr >
HRESULT STDMETHODCALLTYPE my_Present( IDXGISwapChain* This, UINT SyncInterval, UINT Flags )
{
	log_frame( "dxgi", u::info ) << log_var(This) << u::endh;
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC desc;
	hr = This->GetDesc( &desc );
	frame << log_var(desc.BufferDesc.Width) << log_var(desc.BufferDesc.Height) << log_var(desc.OutputWindow);

	CComPtr<IDXGIDevice> dxgiDevice;
	hr = This->GetDevice( __uuidof(IDXGIDevice), (void**)&dxgiDevice );
	frame << log_var(dxgiDevice);

	HRESULT result = Tr::stub()(This, SyncInterval, Flags );
	frame << log_ret(result);
	return result;
}

HRESULT STDMETHODCALLTYPE my_Present1( IDXGISwapChain1* This, UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters )
{
	log_frame( "dxgi", u::info ) << log_var(This) << u::endh;
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC1 desc;
	hr = This->GetDesc1( &desc );
	frame << log_var(desc.Width) << log_var(desc.Height);

	HWND hwnd;
	hr = This->GetHwnd( &hwnd );
	frame << log_var(hwnd);

	CComPtr<IDXGIDevice> dxgiDevice;
	hr = This->GetDevice( __uuidof(IDXGIDevice), (void**)&dxgiDevice );
	frame << log_var(dxgiDevice);

	HRESULT result = (*stub_Present1)(This, SyncInterval, PresentFlags, pPresentParameters );
	frame << log_ret(result);
	return result;
}


void STDMETHODCALLTYPE my_BeginDraw( ID2D1RenderTarget* This )
{
	log_frame( "d2d1", u::info ) << log_var(This) << u::endh;
	(*stub_BeginDraw)( This );
	return;
}


template< typename Tr >
HRESULT STDMETHODCALLTYPE my_EndDraw( ID2D1RenderTarget* This, D2D1_TAG *tag1, D2D1_TAG *tag2 )
{
	HRESULT hr;
	log_frame( "d2d1", u::info ) << log_var(Tr::name()) << log_var(This) << u::endh;


	CComPtr<ID2D1SolidColorBrush> ifBrushBlack;
	CComPtr<ID2D1SolidColorBrush> ifBrushRed;
	CComPtr<ID2D1SolidColorBrush> ifBrushGreen;
	CComPtr<ID2D1SolidColorBrush> ifBrushBlue;

	hr = This->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Black ), &ifBrushBlack );
	hr = This->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Red ), &ifBrushRed );
	hr = This->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Green ), &ifBrushGreen );
	hr = This->CreateSolidColorBrush( D2D1::ColorF( D2D1::ColorF::Blue ), &ifBrushBlue );

	D2D1_RECT_F rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 1024;
	rect.bottom = 2014;
	//This->PushAxisAlignedClip( &rect, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE );
	//This->DrawLine( D2D1::Point2F(0.0f, 0.0f), D2D1::Point2F(480.0f, 480.0f), ifBrush );

    if( !g_fRosebud ) {
	    for( int i=0; i<20; ++i ) {

		    for( int j=0; j<20; ++j ) {
			    float cy = i * 50.0f;
			    float cx = j * 50.0f;

			    ID2D1SolidColorBrush* ifBrush = 
				    ( i<10 && j < 10 ) ? ifBrushBlack :
				    ( i<10 ) ? ifBrushRed :
				    ( j<10 ) ? ifBrushGreen :
				    ifBrushBlue;

			    This->DrawLine( D2D1::Point2F( cx - 5.0f, cy - 5.0f ), D2D1::Point2F( cx + 5.0f, cy + 5.0f ), ifBrush );
			    This->DrawLine( D2D1::Point2F( cx + 5.0f, cy - 5.0f ), D2D1::Point2F( cx - 5.0f, cy + 5.0f ), ifBrush );
		    }
	    }
	    //This->PopAxisAlignedClip();
    }
    else {
        CPlug* pplug = CPlug::inst();
        if( pplug ) {
            bool f = pplug->getRosebudCoord();

            if( f ) {
                float left = (float)g_ptMark.x;
                float top = (float)g_ptMark.y;
                float right = left + g_markWidth;
                float bottom = top + g_markHeight;

                This->DrawLine( D2D1::Point2F(left, top), D2D1::Point2F(right, top), ifBrushBlack );
                This->DrawLine( D2D1::Point2F(right, top), D2D1::Point2F(right, bottom), ifBrushBlack );
                This->DrawLine( D2D1::Point2F(right, bottom), D2D1::Point2F(left, bottom), ifBrushBlack );
                This->DrawLine( D2D1::Point2F(left, bottom), D2D1::Point2F(left, top), ifBrushBlack );
            }
        }

    }

	HRESULT result = Tr::stub()(This, tag1, tag2 );
	frame << log_ret(result);
	return result;
}


HRESULT STDMETHODCALLTYPE my_CreateWicBitmapRenderTarget( ID2D1Factory* This, IWICBitmap* target, const D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties, ID2D1RenderTarget** renderTarget )
{
	log_frame( "d2d1", u::info ) << log_var(This) << log_var(target) << u::endh;

	// Some data about the bitmap
	UINT width, height;
	double dpix, dpiy;
	target->GetSize( &width, &height );
	target->GetResolution( &dpix, &dpiy );
	frame << log_var(width) << log_var(height);
	frame << log_var(dpix) << log_var(dpiy);

	HRESULT result = (*stub_CreateWicBitmapRenderTarget)( This, target, renderTargetProperties, renderTarget );
	
	frame << log_var(*renderTarget) << log_ret(result);
	return result;
}


void STDMETHODCALLTYPE my_DrawGlyphRun( ID2D1RenderTarget* This, D2D1_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN* glyphRun, ID2D1Brush *foregroundBrush, DWRITE_MEASURING_MODE measuringMode )
{
	log_frame( "d2d1", u::info ) << log_var(This) << log_var(baselineOrigin.x) << log_var(baselineOrigin.y) <<
		log_var(glyphRun->glyphCount) << u::endh;

	(*stub_DrawGlyphRun)( This, baselineOrigin, glyphRun, foregroundBrush, measuringMode );
	
	return;
}

HRESULT STDMETHODCALLTYPE my_CreateBitmapFromWicBitmap( ID2D1RenderTarget* This, IWICBitmapSource* wicBitmapSource, const D2D1_BITMAP_PROPERTIES* bitmapProperties, ID2D1Bitmap** bitmap )
{
	log_frame( "d2d1", u::info ) << log_var(This) << log_var(wicBitmapSource);

	double dpix, dpiy;
	UINT width, height;
	wicBitmapSource->GetResolution( &dpix, &dpiy );
	wicBitmapSource->GetSize( &width, &height );
	frame << log_var(dpix) << log_var(dpiy) << log_var(width) << log_var(height) << u::endh;

	HRESULT result = (*stub_CreateBitmapFromWicBitmap)( This, wicBitmapSource, bitmapProperties, bitmap );

	frame << log_var(*bitmap) << log_ret(result);
	return result;
}

void STDMETHODCALLTYPE my_DrawBitmap( ID2D1RenderTarget* This, ID2D1Bitmap* bitmap, const D2D1_RECT_F* destRc, FLOAT opacity, 
								  D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F* srcRc )
{
	log_frame( "d2d1", u::info ) << log_var(This) << log_var(bitmap) << log_var(opacity);

	D2D1_SIZE_F bitmapSize = bitmap->GetSize( );
	frame << log_var(bitmapSize.width) << log_var(bitmapSize.height);

	if( destRc ) {
		frame << log_var(destRc->left) << log_var(destRc->top) << log_var(destRc->right) << log_var(destRc->bottom);
	}

	if( srcRc ) {
		frame << log_var(srcRc->left) << log_var(srcRc->top) << log_var(srcRc->right) << log_var(srcRc->bottom);
	}

	frame << u::endh;

	(*stub_DrawBitmap)(This, bitmap, destRc, opacity, interpolationMode, srcRc );

	return;
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
	//{ &(void*&)stub_Present_1, (type_Present)my_Present<tr_Present_1> },
	//{ &(void*&)stub_Present_2, (type_Present)my_Present<tr_Present_2> },
	hook(Present1),
	hook(BeginDraw),
	{ &(void*&)stub_EndDraw_1, (type_EndDraw)my_EndDraw<tr_EndDraw_1> },
	{ &(void*&)stub_EndDraw_2, (type_EndDraw)my_EndDraw<tr_EndDraw_2> },
	{ &(void*&)stub_EndDraw_3, (type_EndDraw)my_EndDraw<tr_EndDraw_3> },
	{ &(void*&)stub_EndDraw_4, (type_EndDraw)my_EndDraw<tr_EndDraw_4> },
	{ &(void*&)stub_EndDraw_5, (type_EndDraw)my_EndDraw<tr_EndDraw_5> },
	{ &(void*&)stub_CreateWicBitmapRenderTarget, my_CreateWicBitmapRenderTarget },
	{ &(void*&)stub_DrawGlyphRun, my_DrawGlyphRun },
	{ &(void*&)stub_CreateBitmapFromWicBitmap, my_CreateBitmapFromWicBitmap },
	{ &(void*&)stub_DrawBitmap, my_DrawBitmap },
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

	stub_Present_1 = static_cast<type_Present>( DetourFindFunction( "dxgi.dll", symbol_Present_1 ) );
	stub_Present_2 = static_cast<type_Present>( DetourFindFunction( "dxgi.dll", symbol_Present_2 ) );

	stub_Present1 = static_cast<type_Present1>( DetourFindFunction( "dxgi.dll", symbol_Present1 ) );

	stub_BeginDraw = static_cast<type_BeginDraw>( DetourFindFunction( "d2d1.dll", symbol_BeginDraw ) );

	stub_EndDraw_1 = static_cast<type_EndDraw>( DetourFindFunction( "d2d1.dll", symbol_EndDraw_1 ) );
	stub_EndDraw_2 = static_cast<type_EndDraw>( DetourFindFunction( "d2d1.dll", symbol_EndDraw_2 ) );
	stub_EndDraw_3 = static_cast<type_EndDraw>( DetourFindFunction( "d2d1.dll", symbol_EndDraw_3 ) );
	stub_EndDraw_4 = static_cast<type_EndDraw>( DetourFindFunction( "d2d1.dll", symbol_EndDraw_4 ) );
	stub_EndDraw_5 = static_cast<type_EndDraw>( DetourFindFunction( "d2d1.dll", symbol_EndDraw_5 ) );

	stub_CreateWicBitmapRenderTarget = static_cast<type_CreateWicBitmapRenderTarget>( DetourFindFunction( "d2d1.dll", symbol_CreateWicBitmapRenderTarget ) );
	stub_DrawGlyphRun = static_cast<type_DrawGlyphRun>( DetourFindFunction( "d2d1.dll", symbol_DrawGlyphRun ) );
	stub_CreateBitmapFromWicBitmap = static_cast<type_CreateBitmapFromWicBitmap>( DetourFindFunction( "d2d1.dll", symbol_CreateBitmapFromWicBitmap ) );
	stub_DrawBitmap = static_cast<type_DrawBitmap>( DetourFindFunction( "d2d1.dll", symbol_DrawBitmap ) );
}

void attachDetours( )
{
	LONG result, result1;

	resolveAddresses();

    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread() );
	for( HookRecord& h : g_hooks ) {
		if( *h.ptr ) {
		    result1 = DetourAttach( h.ptr, h.detour );
		}
	};
    result = DetourTransactionCommit( );
}


void detachDetours( )
{
    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread() );
	for( HookRecord& h : g_hooks ) {
		if( *h.ptr ) {
	        DetourDetach( h.ptr, h.detour );
		}
	}
    DetourTransactionCommit( );
}
