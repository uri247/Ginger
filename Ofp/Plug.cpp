// Plug.cpp : Implementation of CPlug

#include "stdafx.h"
#include "Plug.h"



_ATL_FUNC_INFO FuncInfo_DocumentOpen = { CC_STDCALL, VT_EMPTY, 1, { VT_BYREF|VT_USERDEFINED }   };
_ATL_FUNC_INFO FuncInfo_NewDocument = { CC_STDCALL, VT_EMPTY, 1, { VT_BYREF|VT_USERDEFINED }   };


CPlug::CPlug() 
{
}


HRESULT
CPlug::FinalConstruct()
{
	return S_OK;
}


void
CPlug::FinalRelease()
{
}


STDMETHODIMP CPlug::OnConnection( IDispatch *dispApplication, addin::ext_ConnectMode connectMode, IDispatch* dispAddIn, SAFEARRAY** custom )
{
	HRESULT hr = S_OK;
	CComPtr<word::_Application> ifWord;

	if( SUCCEEDED(hr) ) {
	    hr = dispApplication->QueryInterface( &ifWord );
	}

	if( SUCCEEDED(hr) ) {
		hr = EventImpl_Word::DispEventAdvise( dispApplication );
	}

	return hr;
}


STDMETHODIMP CPlug::OnDisconnection( addin::ext_DisconnectMode removeMode, SAFEARRAY** custom )
{
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
	MessageBox( NULL, L"hello", L"world", MB_OK );
    return S_OK;
}

STDMETHODIMP CPlug::OnNewDocument ( word::_Document* ifDoc )
{
	return S_OK;
}





