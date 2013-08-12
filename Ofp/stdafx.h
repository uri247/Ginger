
// C++ Runtime
#include <string>
#include <functional>
#include <array>
#include <algorithm>

using std::min;
using std::max;

// Windows
#define _WIN32_WINNT            0x0601
#define WIN32_LEAN_AND_MEAN     1
#define STRICT                  1
#define NOMINMAX                1
#include <Windows.h>
#include <ShlObj.h>
#include <gdiplus.h>
#include <d3d11_1.h>
#include <d2d1_1.h>
#include <dxgi.h>


// ATL
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      1
#define _ATL_APARTMENT_THREADED                 1
#define _ATL_DEBUG_QI                           1
#define _ATL_DEBUG_INTERFACES                   1
#include <atlbase.h>
#include <atltypes.h>
#include <atlcom.h>
#include <atlwin.h>

// Office
#undef ExitWindows
/*
#import <msaddndr.tlb> raw_interfaces_only raw_native_types rename_namespace("addin")
#import <mso.tlb> raw_interfaces_only raw_native_types rename_namespace("mso") rename("RGB","mso_RGB")
#import <word.tlb> raw_interfaces_only raw_native_types rename_namespace("word")
#import <excel.tlb> raw_interfaces_only raw_native_types rename_namespace("excel") rename("RGB","excel_RGB") rename("CopyFile","excel_CopyFile") rename("DialogBox","excel_DialogBox") exclude("IFont","IPicture")
*/
#include <msaddndr.tlh>
#include <mso.tlh>
#include <word.tlh>



// Detour
#include <detours.h>

