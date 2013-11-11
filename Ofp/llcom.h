
#ifdef __cplusplus
extern "C" {
#endif



char const* const symbol_CreateSwapChain = "?CreateSwapChain@CDXGIFactory@@UAGJPAUIUnknown@@PAUDXGI_SWAP_CHAIN_DESC@@PAPAUIDXGISwapChain@@@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_CreateSwapChain)( IDXGIFactory* This, IUnknown* ifDevice, DXGI_SWAP_CHAIN_DESC* pdesc, IDXGISwapChain** ppSwapChain );
type_CreateSwapChain resolve_CreateSwapChain( IDXGIFactory* dxgiFactory );


char const* const symbol_CreateSwapChainForHwnd = "?CreateSwapChainForHwnd@CDXGIFactory@@UAGJPAUIUnknown@@PAUHWND__@@PBUDXGI_SWAP_CHAIN_DESC1@@PBUDXGI_SWAP_CHAIN_FULLSCREEN_DESC@@PAUIDXGIOutput@@PAPAUIDXGISwapChain1@@@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_CreateSwapChainForHwnd)( IDXGIFactory2* This, IUnknown* pDevice, HWND hWnd, const DXGI_SWAP_CHAIN_DESC1* pDesc, 
	const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** ppSwapChain );
type_CreateSwapChainForHwnd resolve_CreateSwapChainForHwnd( IDXGIFactory2* dxgiFactory2 );


/* All Present function goes here. See IDA pro
.text:10001D06 ; public: long __thiscall CDXGISwapChain::PresentImpl(enum  EPresentEntryPoint, unsigned int, unsigned int, unsigned int, struct tagRECT const *, unsigned int, struct DXGI_SCROLL_RECT const *, struct IDXGIResource *)
.text:10001D06 ?PresentImpl@CDXGISwapChain@@QAEJW4EPresentEntryPoint@@IIIPBUtagRECT@@IPBUDXGI_SCROLL_RECT@@PAUIDXGIResource@@@Z proc near
*/


char const* const symbol_Present_1 = "?Present@CDXGISwapChain@@UAGJII@Z";
char const* const symbol_Present_2 = "?Present@?$CDXGISwapChainBase@UIDXGISwapChain@@@@UAGJII@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_Present)( IDXGISwapChain* This, UINT SyncInterval, UINT Flags );
type_Present resolve_Present( IDXGISwapChain* This );


char const* const symbol_Present1 = "?Present1@?IIDXGISwapChain1@CDXGISwapChain@@UAGJIIPBUDXGI_PRESENT_PARAMETERS@@@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_Present1)( IDXGISwapChain1* This, UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters );
type_Present1 resolve_Present1( IDXGISwapChain1* This );


char const* const symbol_BeginDraw = "?BeginDraw@?$D2DRenderTargetBase@UID2D1BitmapRenderTarget@@@@UAGXXZ";
typedef void (STDMETHODCALLTYPE* type_BeginDraw)( ID2D1RenderTarget* This );

char const* const symbol_EndDraw_1 = "?EndDraw@?$D2DDeviceContextBase@UID2D1BitmapRenderTarget@@U1@UID2D1DeviceContext@@@@UAGJPA_K0@Z";
char const* const symbol_EndDraw_2 = "?EndDraw@?$D2DDeviceContextBase@UID2D1HwndRenderTarget@@U1@UID2D1DeviceContext@@@@UAGJPA_K0@Z";
char const* const symbol_EndDraw_3 = "?EndDraw@?$D2DDeviceContextBase@UID2D1DeviceContext@@U1@Vnull_type@@@@UAGJPA_K0@Z";
char const* const symbol_EndDraw_4 = "?EndDraw@?$D2DDeviceContextBase@UID2D1RenderTarget@@UID2D1DeviceContext@@U2@@@UAGJPA_K0@Z";
char const* const symbol_EndDraw_5 = "?EndDraw@?$D2DRenderTargetBase@UID2D1BitmapRenderTarget@@@@UAGJPA_K0@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_EndDraw)( ID2D1RenderTarget* This, D2D1_TAG *tag1, D2D1_TAG *tag2 );
type_EndDraw resolve_EndDraw( ID2D1RenderTarget* This );


char const* const symbol_CreateWicBitmapRenderTarget = "?CreateWicBitmapRenderTarget@D2DFactory@@UAGJPAUIWICBitmap@@PBUD2D1_RENDER_TARGET_PROPERTIES@@PAPAUID2D1RenderTarget@@@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_CreateWicBitmapRenderTarget)( ID2D1Factory* This, IWICBitmap* target, const D2D1_RENDER_TARGET_PROPERTIES *renderTargetProperties, ID2D1RenderTarget** renderTarget );

       
char const* const symbol_DrawGlyphRun = "?DrawGlyphRun@?$D2DDeviceContextBase@UID2D1BitmapRenderTarget@@U1@UID2D1DeviceContext@@@@UAGXUD2D_POINT_2F@@PBUDWRITE_GLYPH_RUN@@PAUID2D1Brush@@W4DWRITE_MEASURING_MODE@@@Z";
//char const* const symbol_DrawGlyphRun = "?DrawGlyphRun@?$D2DRenderTargetBase@UID2D1HwndRenderTarget@@@@UAGXUD2D_POINT_2F@@PBUDWRITE_GLYPH_RUN@@PAUID2D1Brush@@W4DWRITE_MEASURING_MODE@@@Z";
typedef void (STDMETHODCALLTYPE* type_DrawGlyphRun)( ID2D1RenderTarget* This, D2D1_POINT_2F baselineOrigin, const DWRITE_GLYPH_RUN *glyphRun, ID2D1Brush *foregroundBrush, DWRITE_MEASURING_MODE measuringMode );

char const* const symbol_CreateBitmapFromWicBitmap = "?CreateBitmapFromWicBitmap@?$D2DRenderTargetBase@UID2D1RenderTarget@@@@UAGJPAUIWICBitmapSource@@PBUD2D1_BITMAP_PROPERTIES@@PAPAUID2D1Bitmap@@@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_CreateBitmapFromWicBitmap)( ID2D1RenderTarget* This, IWICBitmapSource* wicBitmapSource, const D2D1_BITMAP_PROPERTIES* bitmapProperties, ID2D1Bitmap** bitmap );

char const* const symbol_DrawBitmap = "?DrawBitmap@?$D2DRenderTargetBase@UID2D1RenderTarget@@@@UAGXPAUID2D1Bitmap@@PBUD2D_RECT_F@@MW4D2D1_BITMAP_INTERPOLATION_MODE@@1@Z";
typedef void (STDMETHODCALLTYPE* type_DrawBitmap)( ID2D1RenderTarget* This, ID2D1Bitmap* bitmap, const D2D1_RECT_F *destinationRectangle, FLOAT opacity,
											 D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F *sourceRectangle );


#ifdef __cplusplus
}
#endif

