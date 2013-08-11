#include "stdafx.h"
#include "trace.h"
#include "Plug.h"
#include "Subcls.h"

HDC (WINAPI* stub_GetDC)( HWND ) = ::GetDC;
int (WINAPI* stub_ReleaseDC)( HWND, HDC ) = ::ReleaseDC;
BOOL (WINAPI* stub_BitBlt)( HDC, int, int, int, int, HDC, int, int, DWORD ) = ::BitBlt;
BOOL (WINAPI* stub_UpdateLayeredWindow)( HWND, HDC, POINT*, SIZE*, HDC, POINT*, COLORREF, BLENDFUNCTION*, DWORD ) = ::UpdateLayeredWindow;
LRESULT (WINAPI* stub_DispatchMessage)( const MSG* ) = ::DispatchMessage;
//HRESULT (WINAPI* stub_CreateDXGIFactory1)( REFIID riid, void **ppFactory ) = ::CreateDXGIFactory1;
HRESULT (WINAPI* stub_CreateDXGIFactory1)( REFIID riid, void **ppFactory ) = static_cast<HRESULT(WINAPI*)(const IID&, void**)>(DetourFindFunction( "dxgi.dll", "CreateDXGIFactory1" ));


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
	log_frame( "riid", u::info ) << u::endh;
	HRESULT result = (*stub_CreateDXGIFactory1)(riid, ppFactory);
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
	hook(CreateDXGIFactory1),
};

void attachDetours( )
{
	//void* fn = DetourFindFunction( "dxgi.dll", "CreateDXGIFactory1" );

    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread() );
	for( HookRecord& h : g_hooks ) {
		DetourAttach( h.ptr, h.detour );
	};
    DetourTransactionCommit( );
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
