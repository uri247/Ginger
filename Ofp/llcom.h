
#ifdef __cplusplus
extern "C" {
#endif

typedef HRESULT (STDMETHODCALLTYPE* type_CreateSwapChain)(IDXGIFactory* This, IUnknown* ifDevice, DXGI_SWAP_CHAIN_DESC* pdesc, IDXGISwapChain** ppSwapChain );
type_CreateSwapChain resolve_CreateSwapChain( IDXGIFactory* dxgiFactory );


#ifdef __cplusplus
}
#endif

