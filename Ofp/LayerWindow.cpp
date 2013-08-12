#include "stdafx.h"
#include "LayerWindow.h"


void CLayeredWindow::createDib()
{
	BITMAPINFO bi = {};
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_info.GetWidth();
	bi.bmiHeader.biHeight = 0 - m_info.GetHeight();
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	void* bits = 0;

	HBITMAP hbitmap = CreateDIBSection( 0, &bi, DIB_RGB_COLORS, &bits, 0, 0 );
}
