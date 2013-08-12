#include <dxgi.h>
#include "llcom.h"


type_CreateSwapChain resolve_CreateSwapChain( IDXGIFactory* dxgiFactory ) {
	type_CreateSwapChain fn = dxgiFactory->lpVtbl->CreateSwapChain;
	return fn;
}


