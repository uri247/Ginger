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
		MESSAGE_HANDLER( WM_CHAR, onChar )
		MESSAGE_HANDLER( WM_PAINT, onPaint )
    END_MSG_MAP()

public:
	void highlight( );

private:
	LRESULT onChar( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled );
	LRESULT onPaint( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled );
};
