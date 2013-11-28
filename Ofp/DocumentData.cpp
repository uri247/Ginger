#include "stdafx.h"
#include "wndtools.h"
#include "DocumentData.h"


CDocumentData* CDocumentDataManager::getDocumentData( word::_Document* ifDoc )
{
    auto it = m_map.find( ifDoc );

    if( it == m_map.end() ) {
        //auto p = m_map.emplace( ifDoc, std::unique_ptr<CDocumentData>( new CDocumentData(ifDoc) ) );
		auto p = m_map.emplace(ifDoc, std::make_unique<CDocumentData>(ifDoc));
        it = p.first;
    }

    std::unique_ptr<CDocumentData>& up = it->second;
    CDocumentData* p = up.get();
    return p;

};


void CDocumentDataManager::removeDocumentData( word::_Document* ifDoc )
{
    auto it = m_map.find( ifDoc );
    if( it != m_map.end() ) {
        m_map.erase(it);
    }
}



HWND CDocumentData::hwnd()
{
    HWND hwndTop;
	HRESULT hr;
	long numWindows;
    HWND hwnd;

    if( m_hwnd == NULL ) {

	    // Verify we have only one window for the document (TODO: handle that case later)
	    CComPtr<word::Windows> ifWindows;
	    hr = m_ifDoc->get_Windows( &ifWindows );

	    hr = ifWindows->get_Count( &numWindows );
	    ATLTRACE( "There are currently %d windows for current document", numWindows );

	    CComPtr<word::Window> ifWindow;
	    CComVariant varNdx = ( (long)1 );
	    hr = ifWindows->Item( &varNdx, &ifWindow );

	    ifWindow->get_Hwnd( (long*)&hwndTop );

	    // Find the child window
	    hwnd = findChildWindow( hwndTop, [](HWND hwnd) -> bool {
		    wchar_t klass[200];
            GetClassName( hwnd, klass, _countof(klass) );
		    ATLTRACE( "child window: %ls\n", klass );
		    return !wcscmp( klass, L"_WwG" );
	    });

        m_hwnd = hwnd;
    }

    return m_hwnd;
}
