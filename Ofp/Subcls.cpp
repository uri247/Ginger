#include "stdafx.h"
#include "Subcls.h"

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
	fhandled = FALSE;
	return 0;
}

LRESULT CSubclsWnd::onPaint( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled )
{
	HDC hdc;
	RECT rect;
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
	HDC hdc;
	RECT rect;

	// then, draw diagonal
	GetClientRect( &rect );
	hdc = GetDC();
	MoveToEx( hdc, rect.left, rect.top, NULL );
	LineTo( hdc, rect.right, rect.bottom );
	MoveToEx( hdc, rect.left, rect.bottom, NULL );
	LineTo( hdc, rect.right, rect.top );
	ReleaseDC(hdc);

}

