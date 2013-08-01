#pragma once
using namespace ATL;

class CSubclsWnd: public CWindowImpl<CSubclsWnd, CWindow, CFrameWinTraits>
{
public:
    typedef std::function<void()> Functor;

public:
    CSubclsWnd( );
    ~CSubclsWnd( );
    void Initialize( );

public:
    BEGIN_MSG_MAP(CSubclsWnd)
        MESSAGE_HANDLER( WM_CREATE, onCreate )
    END_MSG_MAP()

private:
    LRESULT onCreate( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled );

};
