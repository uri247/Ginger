#include "stdafx.h"

const char* symbol_path = "srv*http://msdl.microsoft.com/download/symbols";
const char* images[] = {
    "c:\\Windows\\SysWOW64\\dxgi.dll",
    //"c:\\Windows\\SysWOW64\\d2d1.dll",
};



int wmain(int argc, char* argv[])
{
    HANDLE hproc;
    BOOL result;
    DWORD options;
    DWORD64 base;
    IMAGEHLP_MODULE64 info;

    hproc = GetCurrentProcess( );

    result = SymInitialize( hproc, NULL, FALSE );


    options = SYMOPT_IGNORE_IMAGEDIR | SYMOPT_IGNORE_NT_SYMPATH | SYMOPT_EXACT_SYMBOLS | SYMOPT_FAIL_CRITICAL_ERRORS | SYMOPT_IGNORE_CVREC;
    SymSetOptions( options );

    result = SymSetSearchPath( hproc, symbol_path );

    for( const auto image : images ) {
        base = SymLoadModule64( hproc, NULL, image, NULL, 0, 0 );
        memset( &info, 0, sizeof(info) );
        info.SizeOfStruct = sizeof(info);
        result = SymGetModuleInfo64( hproc, base, &info );
    }

	return 0;
}

