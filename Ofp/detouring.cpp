#include "stdafx.h"
#include "trace.h"

HDC (WINAPI* stub_GetDC)( HWND ) = ::GetDC;
int (WINAPI* stub_ReleaseDC)( HWND, HDC ) = ::ReleaseDC;
BOOL (WINAPI* stub_BitBlt)( HDC, int, int, int, int, HDC, int, int, DWORD ) = ::BitBlt;



HDC WINAPI my_GetDC( HWND hwnd )
{
	log_frame( "user", u::info ) << log_var(hwnd) << u::endh;

	HDC hdc = (*stub_GetDC)( hwnd );

	frame << log_ret(hdc);
	return hdc;
}

int WINAPI my_ReleaseDC( HWND hwnd, HDC hdc )
{
	log_frame( "use", u::info ) << log_var(hwnd) << log_var(hdc) << u::endh;

	int result = ReleaseDC( hwnd, hdc );

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



// ----------------------------------------
#define hook(fn)      { &(void*&)stub_##fn, my_##fn }

struct HookRecord {
	void** ptr;
	void* detour;
} g_hooks[] = {
	hook(GetDC),
	//hook(ReleaseDC),
	//hook(BitBlt),
};


void attachAll( )
{
	for( HookRecord& h : g_hooks ) {
		DetourAttach( h.ptr, h.detour );
	};
}

void detachAll( )
{
	for( HookRecord& h : g_hooks ) {
	    DetourDetach( h.ptr, h.detour );
	}
}

void attachDetours( )
{
    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread() );
	attachAll( );
    DetourTransactionCommit( );
}


void detachDetours( )
{
    DetourTransactionBegin( );
    DetourUpdateThread( GetCurrentThread() );
	detachAll( );
    DetourTransactionCommit( );
}
