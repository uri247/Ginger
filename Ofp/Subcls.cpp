#include "stdafx.h"
#include "Subcls.h"
#include "trace.h"

const UINT WM_ASYNC_TASK = RegisterWindowMessage(L"Async-Task");


CSubclsWnd::CSubclsWnd( )
{
}

CSubclsWnd::~CSubclsWnd( )
{
    this->Detach();
}

void CSubclsWnd::Initialize( )
{
    //this->Create( NULL );
}

LRESULT CSubclsWnd::onChar( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled )
{
	InvalidateRect( NULL );
	fhandled = FALSE;
	return 0;
}


void CSubclsWnd::filter (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID )
{
	ATLTRACE( "message: %x\n", uMsg );
}

LRESULT CSubclsWnd::onPaint( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled )
{
	log_frame( "wnd", u::info ) << log_var(msg) << log_var(wparam) << log_var(lparam) << u::endh;

	LRESULT lres;

	// First - call the default windows proc
	lres = this->DefWindowProcW( msg, wparam, lparam );

	// then, highlight the word
	highlight();

	fhandled = TRUE;
	return lres;
}


void CSubclsWnd::highlight( )
{
	log_frame( "ging", u::info ) << u::endh;

	HDC hdc;
	RECT rect;

	if( !m_hWnd ) {
		return;
	}

	// then, draw diagonal
	GetClientRect( &rect );
	hdc = GetDC();
	MoveToEx( hdc, rect.left, rect.top, NULL );
	LineTo( hdc, rect.right, rect.bottom );
	MoveToEx( hdc, rect.left, rect.bottom, NULL );
	LineTo( hdc, rect.right, rect.top );
	ReleaseDC(hdc);
}

