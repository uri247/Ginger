
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


char const* const symbol_Present = "?Present@CDXGISwapChain@@UAGJII@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_Present)( IDXGISwapChain* This, UINT SyncInterval, UINT Flags );
type_Present resolve_Present( IDXGISwapChain* This );


char const* const symbol_Present1 = "?Present1@?IIDXGISwapChain1@CDXGISwapChain@@UAGJIIPBUDXGI_PRESENT_PARAMETERS@@@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_Present1)( IDXGISwapChain1* This, UINT SyncInterval, UINT PresentFlags, const DXGI_PRESENT_PARAMETERS *pPresentParameters );
type_Present1 resolve_Present1( IDXGISwapChain1* This );


char const* const symbol_EndDraw1 = "?EndDraw@?$D2DDeviceContextBase@UID2D1BitmapRenderTarget@@U1@UID2D1DeviceContext@@@@UAGJPA_K0@Z";
char const* const symbol_EndDraw2 = "?EndDraw@?$D2DDeviceContextBase@UID2D1HwndRenderTarget@@U1@UID2D1DeviceContext@@@@UAGJPA_K0@Z";
char const* const symbol_EndDraw3 = "?EndDraw@?$D2DDeviceContextBase@UID2D1DeviceContext@@U1@Vnull_type@@@@UAGJPA_K0@Z";
char const* const symbol_EndDraw4 = "?EndDraw@?$D2DDeviceContextBase@UID2D1RenderTarget@@UID2D1DeviceContext@@U2@@@UAGJPA_K0@Z";
typedef HRESULT (STDMETHODCALLTYPE* type_EndDraw)( ID2D1RenderTarget* This, D2D1_TAG *tag1, D2D1_TAG *tag2 );
type_EndDraw resolve_EndDraw( ID2D1RenderTarget* This );





#ifdef __cplusplus
}
#endif

