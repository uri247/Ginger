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
    this->Create( NULL );
}

LRESULT CSubclsWnd::onCreate( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled )
{
    return ERROR_SUCCESS;
}
