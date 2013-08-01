
HWND findWindow( std::function<bool(HWND)> );
HWND findChildWindow( HWND hwndParent, std::function<bool(HWND)> predicat );