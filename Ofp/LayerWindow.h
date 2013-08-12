#pragma once


class LayeredWindowInfo
{
	const POINT m_sourcePosition;
	POINT m_windowPosition;
    CSize m_size;
    BLENDFUNCTION m_blend;
    UPDATELAYEREDWINDOWINFO m_info;

public:

    LayeredWindowInfo( UINT width, UINT height )
		: m_sourcePosition()
	    , m_windowPosition()
	    , m_size( width, height )
	    , m_blend()
        , m_info()
    {
		m_info.cbSize = sizeof(UPDATELAYEREDWINDOWINFO);
        m_info.pptSrc = &m_sourcePosition;
        m_info.pptDst = &m_windowPosition;
        m_info.psize = &m_size;
        m_info.pblend = &m_blend;
        m_info.dwFlags = ULW_ALPHA;

        m_blend.SourceConstantAlpha = 255;
        m_blend.AlphaFormat = AC_SRC_ALPHA;
	}

	void Update( HWND window, HDC source)
	{
		m_info.hdcSrc = source;
		UpdateLayeredWindowIndirect(window, &m_info);
	}

	UINT GetWidth() const { return m_size.cx; }
	UINT GetHeight() const { return m_size.cy; }
};



class GdiBitmap
{
private:
	const UINT m_width;
	const UINT m_height;
	const UINT m_stride;
	void* m_bits;
	HBITMAP m_oldBitmap;
	HDC m_hdc;
	HBITMAP m_bitmap;

public:

	GdiBitmap( UINT width, UINT height ) 
		: m_width(width)
		, m_height(height)
		, m_stride( (width * 32 + 31 )/32 * 4 )
		, m_bits(nullptr)
		, m_oldBitmap(0)
	{
		BITMAPINFO bi = {};
		bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
		bi.bmiHeader.biWidth = width;
		bi.bmiHeader.biHeight = 0 - height;
		bi.bmiHeader.biPlanes = 1;
		bi.bmiHeader.biBitCount = 32;
		bi.bmiHeader.biCompression = BI_RGB;

		m_bitmap = CreateDIBSection(
			0,
			&bi,
			DIB_RGB_COLORS,
			&m_bits,
			0,
			0
			);


		m_hdc = CreateCompatibleDC( m_hdc );

		m_oldBitmap = (HBITMAP)SelectObject( m_hdc, m_bitmap );
	}

	~GdiBitmap() {
		SelectObject( m_hdc, m_oldBitmap );
	}

	UINT GetWidth() const {
		return m_width;
	}

	UINT GetHeight() const {
		return m_height;
	}

	UINT GetStride() const {
		return m_stride;
	}

	void* GetBits() const {
		return m_bits;
	}

	HDC GetDC() const {
		return m_hdc;
	}
};



class CLayeredWindow
	: public ATL::CWindowImpl<CLayeredWindow, ATL::CWindow, ATL::CWinTraits<WS_POPUP, WS_EX_LAYERED | WS_EX_TOPMOST>>
	//: public ATL::CWindowImpl<CLayeredWindow>
{
private:
	LayeredWindowInfo m_info;
	GdiBitmap m_bitmap;
	Gdiplus::Graphics m_graphics;

public:
	BEGIN_MSG_MAP(CLayeredWindow)
		MESSAGE_HANDLER( WM_DESTROY, onDestroy )
	END_MSG_MAP()
	
	CLayeredWindow( )
		: m_info(600, 400)
		, m_bitmap( m_info.GetWidth(), m_info.GetHeight() )
		, m_graphics( m_bitmap.GetDC() )
	{
		CLayeredWindow::Create( 0 );
		ShowWindow( SW_SHOW	);
		render();
    }
  
    void render()
    {
		Gdiplus::Pen pen( Gdiplus::Color(255, 0, 0, 255) );
		m_graphics.DrawLine( &pen, 0, 0, 200, 100 );
		m_info.Update( m_hWnd, m_bitmap.GetDC() );
	}
   
	LRESULT onDestroy( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& fhandled )
	{
		PostQuitMessage(1);
		return 0;
	}

	void createDib();
};



