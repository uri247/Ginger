
#ifdef __cplusplus
extern "C" {
#endif


// Win32 types
typedef HDC( WINAPI* type_GetDC )(HWND);
typedef int (WINAPI* type_ReleaseDC)(HWND, HDC);
typedef BOOL( WINAPI* type_BitBlt )(HDC, int, int, int, int, HDC, int, int, DWORD);
typedef BOOL( WINAPI* type_UpdateLayeredWindow )(HWND, HDC, POINT*, SIZE*, HDC, POINT*, COLORREF, BLENDFUNCTION*, DWORD);
typedef LRESULT( WINAPI* type_DispatchMessage )(const MSG*);
typedef HRESULT( WINAPI* type_CreateDXGIFactory1 )(REFIID riid, void **ppFactory);
typedef HRESULT( WINAPI* type_CreateDXGIFactory )(REFIID riid, void **ppFactory);

// DXGI types
typedef HRESULT( STDMETHODCALLTYPE* type_CreateSwapChain )(IDXGIFactory* This, IUnknown* ifDevice, DXGI_SWAP_CHAIN_DESC* pdesc, IDXGISwapChain** ppSwapChain);
typedef HRESULT( STDMETHODCALLTYPE* type_CreateSwapChainForHwnd )(IDXGIFactory2* This, IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain);
typedef HRESULT( STDMETHODCALLTYPE* type_Present )(IDXGISwapChain* This, UINT SyncInterval, UINT Flags);
typedef HRESULT( STDMETHODCALLTYPE* type_Present1 )(IDXGISwapChain1* This, UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters);

// D2D1 types
typedef HRESULT( STDMETHODCALLTYPE* type_CreateWicBitmapRenderTarget )(ID2D1Factory* This, IWICBitmap* target, const D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties, ID2D1RenderTarget** renderTarget);

typedef void(STDMETHODCALLTYPE* type_BeginDraw)(ID2D1RenderTarget* This);
typedef HRESULT( STDMETHODCALLTYPE* type_EndDraw )(ID2D1RenderTarget* This, D2D1_TAG *tag1, D2D1_TAG *tag2);
typedef void (STDMETHODCALLTYPE* type_DrawGlyphRun)(ID2D1RenderTarget* This, D2D1_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN *glyphRun, ID2D1Brush *foregroundBrush, DWRITE_MEASURING_MODE measuringMode);
typedef HRESULT( STDMETHODCALLTYPE* type_CreateBitmapFromWicBitmap )(ID2D1RenderTarget* This, IWICBitmapSource* wicBitmapSource, const D2D1_BITMAP_PROPERTIES* bitmapProperties, ID2D1Bitmap** bitmap);
typedef void (STDMETHODCALLTYPE* type_DrawBitmap)(ID2D1RenderTarget* This, ID2D1Bitmap* bitmap, const D2D1_RECT_F *destinationRectangle, FLOAT opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F *sourceRectangle);




// DXGI symbols
char const* const symbol_CreateSwapChain = "?CreateSwapChain@CDXGIFactory@@UAGJPAUIUnknown@@PAUDXGI_SWAP_CHAIN_DESC@@PAPAUIDXGISwapChain@@@Z";
char const* const symbol_CreateSwapChainForHwnd = "?CreateSwapChainForHwnd@CDXGIFactory@@UAGJPAUIUnknown@@PAUHWND__@@PBUDXGI_SWAP_CHAIN_DESC1@@PBUDXGI_SWAP_CHAIN_FULLSCREEN_DESC@@PAUIDXGIOutput@@PAPAUIDXGISwapChain1@@@Z";
char const* const symbol_Present = "?Present@CDXGISwapChain@@UAGJII@Z";
char const* const symbol_Present1 = "?Present1@?IIDXGISwapChain1@CDXGISwapChain@@UAGJIIPBUDXGI_PRESENT_PARAMETERS@@@Z";


// There is also:
// ?PresentImpl@CDXGISwapChain@@QAEJW4EPresentEntryPoint@@IIIPBUtagRECT@@IPBUDXGI_SCROLL_RECT@@PAUIDXGIResource@@@Z
// public: long __thiscall CDXGISwapChain::PresentImpl( enum  EPresentEntryPoint, unsigned int, unsigned int, unsigned int, struct tagRECT const *, unsigned int, struct DXGI_SCROLL_RECT const *, struct IDXGIResource * )


// D2D1 symbols
char const* const symbol_CreateWicBitmapRenderTarget = "?CreateWicBitmapRenderTarget@D2DFactory@@UAGJPAUIWICBitmap@@PBUD2D1_RENDER_TARGET_PROPERTIES@@PAPAUID2D1RenderTarget@@@Z";

char const* const symbol_BeginDraw = "?BeginDraw@?$D2DDeviceContextBase@UID2D1DCRenderTarget@@U1@UID2D1DeviceContext@@@@UAGXXZ";
char const* const symbol_EndDraw = "?EndDraw@?$D2DDeviceContextBase@UID2D1BitmapRenderTarget@@U1@UID2D1DeviceContext@@@@UAGJPA_K0@Z";
char const* const symbol_DrawGlyphRun = "?DrawGlyphRun@?$D2DDeviceContextBase@UID2D1BitmapRenderTarget@@U1@UID2D1DeviceContext@@@@UAGXUD2D_POINT_2F@@PBUDWRITE_GLYPH_RUN@@PAUID2D1Brush@@W4DWRITE_MEASURING_MODE@@@Z";
char const* const symbol_CreateBitmapFromWicBitmap = "?CreateBitmapFromWicBitmap@?$D2DRenderTargetBase@UID2D1RenderTarget@@@@UAGJPAUIWICBitmapSource@@PBUD2D1_BITMAP_PROPERTIES@@PAPAUID2D1Bitmap@@@Z";
char const* const symbol_DrawBitmap = "?DrawBitmap@?$D2DDeviceContextBase@UID2D1DeviceContext@@U1@Vnull_type@@@@UAGXPAUID2D1Bitmap@@PBUD2D_RECT_F@@MW4D2D1_BITMAP_INTERPOLATION_MODE@@1@Z";


#ifdef __cplusplus
}
#endif

