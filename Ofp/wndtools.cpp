#include "stdafx.h"
#include "wndtools.h"


HWND findWindow( std::function<bool(HWND)> predicat )
{
	struct Context {
		HWND hwnd;
		std::function<bool(HWND)> predicat;
	} context = { NULL, predicat };

	auto callback = []( HWND hwnd, LPARAM _param ) -> BOOL {
		Context* ctx = (Context*)_param;
		if( ctx->predicat(hwnd) ) {
			ctx->hwnd = hwnd;
			return FALSE;
		}
		else {
			return TRUE;
		}
	};

	EnumWindows( callback, (LPARAM)&context );

	return context.hwnd;
}


HWND findChildWindow( HWND hwndParent, std::function<bool(HWND)> predicat )
{
	struct Context {
		HWND hwnd;
		std::function<bool(HWND)> predicat;
	} context = { NULL, predicat };

	auto callback = []( HWND hwnd, LPARAM _param ) -> BOOL {
		Context* ctx = (Context*)_param;
		if( ctx->predicat(hwnd) ) {
			ctx->hwnd = hwnd;
			return FALSE;
		}
		else {
			return TRUE;
		}
	};


	EnumChildWindows( hwndParent, callback, (LPARAM)&context );
	return context.hwnd;
}