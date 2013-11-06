#include "stdafx.h"

wchar_t winwword_path[] = L"c:\\Program Files (x86)\\Microsoft Office\\2013\\Office15\\WINWORD.EXE";
wchar_t lek_path[] = L"c:\\users\\uril\\Documents\\lek.docx";

wchar_t cmdline[] = L"c:\\Program Files (x86)\\Microsoft Office\\2013\\Office15\\WINWORD.EXE c:\\users\\uril\\Documents\\lek.docx";



int wmain( int argc, wchar_t* argv[] )
{
	BOOL result;
	std::cout << "start WinWord under debugger ..." << std::endl;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset( &si, 0, sizeof(si) );
	si.cb = sizeof(si);

	memset( &pi, 0, sizeof(pi) );


	result = CreateProcess(
		NULL,
		cmdline,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS | DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS,
		//DEBUG_ONLY_THIS_PROCESS,
		NULL,
		NULL,
		&si,
		&pi
		);




	return 0;
}



