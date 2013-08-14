#include <dxgi1_2.h>
#include <d2d1_1.h>
#include "llcom.h"


type_CreateSwapChain resolve_CreateSwapChain( IDXGIFactory* dxgiFactory ) {
	type_CreateSwapChain fn = dxgiFactory->lpVtbl->CreateSwapChain;
	return fn;
}

type_CreateSwapChainForHwnd resolve_CreateSwapChainForHwnd( IDXGIFactory2* dxgiFactory2 ) {
	type_CreateSwapChainForHwnd fn = dxgiFactory2->lpVtbl->CreateSwapChainForHwnd;
	return fn;
}

type_Present resolve_Present( IDXGISwapChain* This ) {
	type_Present fn = This->lpVtbl->Present;
	return fn;
}

type_Present1 resolve_Present1( IDXGISwapChain1* This ) {
	type_Present1 fn = This->lpVtbl->Present1;
	return fn;
}


