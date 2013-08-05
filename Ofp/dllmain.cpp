#include "stdafx.h"
#include "resource.h"
#include "Ofp_i.h"
#include "dllmain.h"
#include "detouring.h"

COfpModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD reason, LPVOID lpReserved)
{
	if( reason == DLL_PROCESS_ATTACH ) {
		attachDetours( );
	}
	if( reason == DLL_PROCESS_DETACH ) {
		detachDetours( );
	}

	hInstance;
	return _AtlModule.DllMain(reason, lpReserved); 
}
