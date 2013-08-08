#pragma once
using namespace ATL;

#define MY_BEGIN_MSG_MAP(theClass) \
	BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) { \
		BOOL bHandled = TRUE; \
		filter( hWnd, uMsg, wParam, lParam, lResult, bHandled ); \
		switch( dwMsgMapID) { \
		case 0:


class CSubclsWnd: public CWindowImpl<CSubclsWnd, CWindow, CFrameWinTraits>
{
public:
    typedef std::function<void()> Functor;

public:
    CSubclsWnd( );
    ~CSubclsWnd( );
    void Initialize( );

public:
    MY_BEGIN_MSG_MAP(CSubclsWnd)
		MESSAGE_HANDLER( WM_CHAR, onChar )
		MESSAGE_HANDLER( WM_PAINT, onPaint )
    END_MSG_MAP()

public:
	void highlight( );

private:
	LRESULT onChar( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled );
	LRESULT onPaint( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled );

private:
    void filter (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0);
};
