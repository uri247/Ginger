#include "stdafx.h"
#include "trace.h"
#include "Plug.h"
#include "wndtools.h"
#include "Subcls.h"
#include "LayerWindow.h"
#include "detouring.h"

_ATL_FUNC_INFO FuncInfo_DocumentOpen = { CC_STDCALL, VT_EMPTY, 1, { VT_BYREF|VT_USERDEFINED } };
_ATL_FUNC_INFO FuncInfo_NewDocument = { CC_STDCALL, VT_EMPTY, 1, { VT_BYREF|VT_USERDEFINED } };
_ATL_FUNC_INFO FuncInfo_DocumentBeforeClose = { CC_STDCALL, VT_EMPTY, 2, { VT_BYREF|VT_USERDEFINED, VT_BYREF|VT_BOOL } };


CPlug* CPlug::l_pinst = NULL;
long g_markLeft, g_markTop, g_markWidth, g_markHeight;
POINT g_ptMark;
bool g_fRosebud = false;
CComPtr<word::Range> g_ifRosebudRange;

CPlug::CPlug()
	:m_pSubclsWnd( NULL )
{
}


CPlug::~CPlug()
{
}


HRESULT
CPlug::FinalConstruct()
{
	l_pinst = this;
	attachDetours();
	return S_OK;
}


void
CPlug::FinalRelease()
{
	detachDetours();
}


STDMETHODIMP CPlug::OnConnection( IDispatch *dispApplication, addin::ext_ConnectMode connectMode, IDispatch* dispAddIn, SAFEARRAY** custom )
{
	HRESULT hr = S_OK;
	CComPtr<word::_Application> ifWord;

	if( SUCCEEDED(hr) ) {
	    hr = dispApplication->QueryInterface( &ifWord );
	}

	m_dispApplication = dispApplication;

	if( SUCCEEDED(hr) ) {
		hr = EventImpl_Word::DispEventAdvise( dispApplication );
	}

	return hr;
}


STDMETHODIMP CPlug::OnDisconnection( addin::ext_DisconnectMode removeMode, SAFEARRAY** custom )
{
	HRESULT hr = S_OK;
	hr = EventImpl_Word::DispEventUnadvise( m_dispApplication );
    return S_OK;
}


STDMETHODIMP CPlug::OnAddInsUpdate( SAFEARRAY** custom )
{
    UNREFERENCED_PARAMETER( custom );
    return S_OK;
}

STDMETHODIMP CPlug::OnStartupComplete( SAFEARRAY** custom )
{
    UNREFERENCED_PARAMETER( custom );
	//subclassAllWindows( );
    return S_OK;
}

STDMETHODIMP CPlug::OnBeginShutdown( SAFEARRAY** custom )
{
    UNREFERENCED_PARAMETER( custom );
    return S_OK;
}

STDMETHODIMP CPlug::GetCustomUI( BSTR RibbonID, BSTR* pRibbonXml )
{
    HINSTANCE hinst = _AtlBaseModule.GetResourceInstance();
    HRSRC hrsrc = FindResource( hinst, MAKEINTRESOURCE(IDR_RIBBON), L"XML" );
    HGLOBAL hres = LoadResource( hinst, hrsrc );
    void* resource = LockResource( hres );
    char* CustomUIXml = (char*)resource;
    HRESULT hr = S_OK;
    
    if( !pRibbonXml ) {
        hr = E_POINTER;
    }
    else {
        CComBSTR CustomUiStr( CustomUIXml );
        *pRibbonXml = CustomUiStr.Detach( );
    }
    return hr;
}


STDMETHODIMP CPlug::OnDocumentOpen( word::_Document* ifDoc )
{
#if HELLO_MSG
	MessageBox( NULL, L"hello", L"world", MB_OK );
#endif
    return S_OK;
}

STDMETHODIMP CPlug::OnNewDocument ( word::_Document* ifDoc )
{
	return S_OK;
}

STDMETHODIMP CPlug::OnDocumentBeforeClose( word::_Document* ifDoc, VARIANT_BOOL* cancel )
{
    if( g_ifRosebudRange ) {
        g_ifRosebudRange.Release();
    }
    return S_OK;
}



STDMETHODIMP CPlug::Smile( IDispatch* dispRibbonCtrl )
{
	log_frame( "plug", u::info ) << u::endh;
	frame << "------------------------------------------------" << u::endr;
    HRESULT hr = S_OK;

    //CComPtr<mso::IRibbonControl> ifRibbonCtrl;
    //hr = dispRibbonCtrl->QueryInterface( &ifRibbonCtrl );

	CComPtr<word::_Document> ifDoc = activeDoc();
	subclassDocWindows( ifDoc );

	return hr;
}


STDMETHODIMP CPlug::Check( IDispatch* dispRibbonCtrl )
{
	log_frame( "plug", u::info ) << u::endh;
	frame << "------------------------------------------------" << u::endr;
	if( m_pSubclsWnd ) {
		m_pSubclsWnd->highlight();
	}

	//m_pLayeredWindow->MoveWindow( 200, 400, 600, 600 );
	return S_OK;
}


STDMETHODIMP CPlug::Bright( IDispatch* dispRibbonCtrl )
{
	log_frame( "plug", u::info ) << u::endh;
	frame << "------------------------------------------------" << u::endr;

	m_pLayeredWindow = new CLayeredWindow();
	//RECT rect = { 200, 200, 400, 600 };
	//m_pLayeredWindow->Create( 0, rect, L"blah", WS_OVERLAPPED | WS_SYSMENU | WS_THICKFRAME, WS_EX_LAYERED );
	//m_pLayeredWindow->ShowWindow( SW_SHOW );

	return S_OK;
}

STDMETHODIMP CPlug::Control( IDispatch* dispRibbonCtrl )
{
	log_frame( "plug", u::info ) << u::endh;
	frame << "------------------------------------------------" << u::endr;

	CComPtr<word::_Document> ifDoc = activeDoc();
	HWND hwnd = getFirstHwnd( ifDoc );
	RECT rect;
	::GetClientRect( hwnd, &rect );
	ClientToScreen( hwnd, (POINT*)&rect );
	ClientToScreen( hwnd, ((POINT*)&rect) + 1 );
	m_pLayeredWindow->MoveWindow( rect.left, rect.top, rect.right, rect.bottom );
	return S_OK;
}


STDMETHODIMP CPlug::Fxwiz( IDispatch* dispRibbonCtrl )
{
    g_fRosebud = true;
    getRosebud();
    return S_OK;
}

bool CPlug::getRosebudCoord( )
{
    HRESULT hr;
	CComPtr<word::_Document> ifDoc;
    bool retval = false;    
   	CComPtr<word::Window> ifWnd;
    HWND hwnd;

    ifDoc = activeDoc();
    if( ifDoc ) {

	    hr = ifDoc->get_ActiveWindow( &ifWnd );
    
        hwnd = getFirstHwnd( ifDoc );

        if( g_ifRosebudRange != NULL ) {
            hr = ifWnd->GetPoint( &g_markLeft, &g_markTop, &g_markWidth, &g_markHeight, g_ifRosebudRange );
            if( SUCCEEDED(hr) ) {
	            g_ptMark.x = g_markLeft;
	            g_ptMark.y = g_markTop;
	            ScreenToClient( hwnd, &g_ptMark );
                retval = true;
            }
        }
    }
    return retval;
}

void CPlug::getRosebud( )
{
	log_frame( "plug", u::info ) << u::endh;
	frame << "------------------------------------------------" << u::endr;
	HRESULT hr;

    if( g_ifRosebudRange != NULL ) {
        g_ifRosebudRange.Release();
    }

	CComPtr<word::_Document> ifDoc;
	ifDoc = activeDoc();

	CComPtr<word::Range> ifRange;
	ifDoc->get_Content( &ifRange );

	CComPtr<word::Find> ifFind;
	ifRange->get_Find( &ifFind );

	hr = ifFind->ClearFormatting();
	CComBSTR rosebud( "rosebud" );
	ifFind->put_Text( rosebud );
	CComVariant vtext( L"rosebud" );
	CComVariant vtrue(true);
	CComVariant vfalse(false);
    CComVariant vnone( word::wdNone );
    VARIANT_BOOL prop;

	hr = ifFind->Execute( 
		&vtext,         // text
		&vtrue,         // case
		&vfalse,        // whole word
        &vfalse,        // whild card
        &vfalse,        // soundex
        &vfalse,        // all word forms
        &vtrue,         // forward
        &vfalse,        // wrap
        &vfalse,        // format
        NULL,           // replace
        &vnone,         // wdNone
        &vfalse,        // match kashida
        &vfalse,        // match diacritics
        &vfalse,        // match alef hamza
        &vfalse,        // match control
        &prop );

    if( prop ) {
        g_ifRosebudRange = ifRange;
    }

}




word::_Document* CPlug::activeDoc( )
{
	HRESULT hr = S_OK;
	CComPtr<word::_Application> ifWord;
	CComPtr<word::_Document> ifDoc;

    if( SUCCEEDED(hr) ) {
        hr = m_dispApplication.QueryInterface( &ifWord );
    }

    if( SUCCEEDED(hr) ) {
	    hr = ifWord->get_ActiveDocument( &ifDoc );
    }

	return ifDoc.Detach();
}


void CPlug::subclassAllWindows( )
{
	HRESULT hr = S_OK;
	CComPtr<word::_Application> ifWord;
	CComPtr<word::_Document> ifDoc;
	CComPtr<word::Documents> ifDocs;
	long numDocs;

	hr = m_dispApplication.QueryInterface( &ifWord );
	hr = ifWord->get_Documents( &ifDocs );

	ifDocs->get_Count( &numDocs );
	for( long i=0; i<numDocs; ++i ) {
		CComVariant varNdx(i);
		CComPtr<word::_Document> ifDoc;
		hr = ifDocs->Item( &varNdx, &ifDoc );
		subclassDocWindows( ifDoc );
	}
}

void CPlug::subclassDocWindows( word::_Document* ifDoc )
{
	HWND hwnd = getFirstHwnd( ifDoc );
	m_pSubclsWnd = new CSubclsWnd();
	m_pSubclsWnd->SubclassWindow( hwnd );
}

HWND CPlug::getFirstHwnd( word::_Document* ifDoc )
{
	HWND hwndTop;
	HRESULT hr;
	long numWindows;
    HWND hwnd;

	// Verify we have only one window for the document (TODO: handle that case later)
	CComPtr<word::Windows> ifWindows;
	hr = ifDoc->get_Windows( &ifWindows );

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

	return hwnd;
}
