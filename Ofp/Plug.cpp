#include "stdafx.h"
#include "trace.h"
#include "Plug.h"
#include "Subcls.h"
#include "LayerWindow.h"
#include "detouring.h"

// class variables
_ATL_FUNC_INFO CPlug::FuncInfo_DocumentOpen = { CC_STDCALL, VT_EMPTY, 1, { VT_BYREF|VT_USERDEFINED } };
_ATL_FUNC_INFO CPlug::FuncInfo_NewDocument = { CC_STDCALL, VT_EMPTY, 1, { VT_BYREF|VT_USERDEFINED } };
_ATL_FUNC_INFO CPlug::FuncInfo_DocumentBeforeClose = { CC_STDCALL, VT_EMPTY, 2, { VT_BYREF|VT_USERDEFINED, VT_BYREF|VT_BOOL } };
CPlug* CPlug::l_pinst = NULL;



// --------------------------------------------------------------

CPlug::CPlug()
	:m_pSubclsWnd( NULL )
    ,m_fDoGrid(false)
    ,m_fDoRosebud(false)
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
    m_docManager.removeDocumentData( ifDoc );
    return S_OK;
}



STDMETHODIMP CPlug::Smile( IDispatch* dispRibbonCtrl )
{
	log_frame( "plug", u::info ) << u::endh;
	frame << "------------------------------------------------" << u::endr;
    HRESULT hr = S_OK;

    //CComPtr<mso::IRibbonControl> ifRibbonCtrl;
    //hr = dispRibbonCtrl->QueryInterface( &ifRibbonCtrl );

	CComPtr<word::_Document> ifDoc;
    hr = getActiveDoc( &ifDoc );

    if( SUCCEEDED(hr) ) {
        subclassDocWindows( ifDoc );
    }

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
    HRESULT hr;
    RECT rect;
    HWND hwnd;
	CComPtr<word::_Document> ifDoc;

	log_frame( "plug", u::info ) << u::endh;
	frame << "------------------------------------------------" << u::endr;

    
    hr = getActiveDoc( &ifDoc );
	hwnd = getFirstHwnd( ifDoc );

    ::GetClientRect( hwnd, &rect );
	ClientToScreen( hwnd, (POINT*)&rect );
	ClientToScreen( hwnd, ((POINT*)&rect) + 1 );
	m_pLayeredWindow->MoveWindow( rect.left, rect.top, rect.right, rect.bottom );
	return S_OK;
}


STDMETHODIMP CPlug::Fxwiz( IDispatch* dispRibbonCtrl )
{
    return S_OK;
}

STDMETHODIMP CPlug::CheckRosebud( IDispatch* ifRibbonCtrl, VARIANT_BOOL state )
{
    if( state ) {
        m_fDoRosebud = true;
        getRosebud();
    }
    else {
        m_fDoRosebud = false;
    }

    return S_OK;
}

STDMETHODIMP CPlug::CheckGrid( IDispatch* ifRibbonCtrl, VARIANT_BOOL state )
{
    if( state ) {
        m_fDoGrid = true;
    }
    else {
        m_fDoGrid = false;
    }
    return S_OK;
}


int CPlug::numRosebuds( )
{
    HRESULT hr;
    CComPtr<word::_Document> ifDoc;
    int num = 0;

    hr = getActiveDoc( &ifDoc );

    if( SUCCEEDED( hr ) )
    {
        CDocumentData* pdocdata;

        pdocdata = m_docManager.getDocumentData( ifDoc );
        num = pdocdata->m_ifRosebudRanges.size( );
    }

    return num;
}

bool CPlug::enumRosebud( int i, int* pleft, int* ptop, int* pright, int* pbottom )
{
    HRESULT hr;
	CComPtr<word::_Document> ifDoc;
    bool retval = false;

    hr = getActiveDoc( &ifDoc );

    if( SUCCEEDED(hr) )
    {
        CDocumentData* pdocdata;

        pdocdata = m_docManager.getDocumentData( ifDoc );
        if( i >=0 && i < (int)pdocdata->m_ifRosebudRanges.size( ) )
        {
            HWND hwnd;
            CComPtr<word::Range> ifRange;
   	        CComPtr<word::Window> ifWnd;

            ifRange = pdocdata->m_ifRosebudRanges[i];
            ATLASSERT( ifRange );
            hr = ifDoc->get_ActiveWindow( &ifWnd );
            hwnd = pdocdata->hwnd( );

            long left, top, width, height;

            hr = ifWnd->GetPoint( &left, &top, &width, &height, ifRange );
            if( SUCCEEDED(hr) ) {
                POINT pt;
                pt.x = left;
                pt.y = top;
                ScreenToClient( hwnd, &pt );

                *pleft = pt.x;
                *ptop = pt.y;
                *pright = *pleft + width;
                *pbottom = *ptop + height;
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
    CDocumentData* pdocdata;
	CComPtr<word::_Document> ifDoc;
    long start, end;

    hr = getActiveDoc( &ifDoc );

    // find the start and end of document
    if( SUCCEEDED( hr ) ) {
        CComPtr<word::Range> ifRange;
        ifDoc->get_Content( &ifRange );
        hr = ifRange->get_Start( &start );
        hr = ifRange->get_End( &end );
    }

    if( SUCCEEDED( hr ) ) {
        pdocdata = m_docManager.getDocumentData( ifDoc );
        pdocdata->m_ifRosebudRanges.clear( );

        while( SUCCEEDED( hr ) )
        {
            // creating a range starting from current start until end of document
            CComPtr<word::Range> ifRange;
            CComVariant vStart( start );
            CComVariant vEnd( end );
            ifDoc->Range( &vStart, &vEnd, &ifRange );

            // get a find interface in the range
            CComPtr<word::Find> ifFind;
            ifRange->get_Find( &ifFind );
            hr = ifFind->ClearFormatting( );
            CComBSTR rosebud( "rosebud" );
            ifFind->put_Text( rosebud );
            CComVariant vtext( L"rosebud" );
            CComVariant vtrue( true );
            CComVariant vfalse( false );
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
                pdocdata->m_ifRosebudRanges.push_back( ifRange );
                ifRange->get_End( &start );
            }
            else {
                break;
            }
        }
    }

}




HRESULT CPlug::getActiveDoc( word::_Document** pifDoc )
{
	HRESULT hr = S_OK;
	CComPtr<word::_Application> ifWord;

    if( SUCCEEDED(hr) ) {
        hr = m_dispApplication.QueryInterface( &ifWord );
    }

    if( SUCCEEDED(hr) ) {
	    hr = ifWord->get_ActiveDocument( pifDoc );
    }

    return hr;
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
    CDocumentData* pdocdata;

    pdocdata = m_docManager.getDocumentData( ifDoc );
    return pdocdata->hwnd();
}
