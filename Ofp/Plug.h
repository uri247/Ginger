#pragma once
#include "resource.h"       // main symbols
#include "Ofp_i.h"
using namespace ATL;

class CPlug;
extern _ATL_FUNC_INFO FuncInfo_DocumentOpen;
extern _ATL_FUNC_INFO FuncInfo_NewDocument;


typedef IDispEventSimpleImpl<1, CPlug, &__uuidof(word::ApplicationEvents4)> EventImpl_Word;



class ATL_NO_VTABLE CPlug
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CPlug, &CLSID_Plug>
	, public IDispatchImpl<IPlug, &IID_IPlug, &LIBID_OfpLib, 1, 0>
	, public IDispatchImpl<addin::_IDTExtensibility2, &__uuidof(addin::_IDTExtensibility2), &__uuidof(addin::__AddInDesignerObjects), 1, 0>
	, public IDispatchImpl<mso::IRibbonExtensibility, &__uuidof(mso::IRibbonExtensibility), &__uuidof(mso::__Office), 1, 0>
	, public EventImpl_Word

{
public:
	DECLARE_REGISTRY_RESOURCEID(IDR_PLUG)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CPlug)
		COM_INTERFACE_ENTRY(addin::IDTExtensibility2)
		COM_INTERFACE_ENTRY(mso::IRibbonExtensibility)
		COM_INTERFACE_ENTRY(IPlug)
		COM_INTERFACE_ENTRY2(IDispatch, IPlug)
	END_COM_MAP()
	BEGIN_SINK_MAP(CPlug)
        SINK_ENTRY_INFO(1, __uuidof(word::ApplicationEvents4), 0x00000004, OnDocumentOpen, &FuncInfo_DocumentOpen )
		SINK_ENTRY_INFO(1, __uuidof(word::ApplicationEvents4), 0x00000009, OnNewDocument, &FuncInfo_NewDocument )
    END_SINK_MAP()

public:
	CPlug();
	HRESULT FinalConstruct();
	void FinalRelease();

public:
    // addin::IDTExtensibility2
    STDMETHOD(OnConnection)( IDispatch *dispApplication, addin::ext_ConnectMode connectMode, IDispatch* dispAddIn, SAFEARRAY** custom );
    STDMETHOD(OnDisconnection)( addin::ext_DisconnectMode removeMode, SAFEARRAY** custom );
    STDMETHOD(OnAddInsUpdate)( SAFEARRAY** custom );
    STDMETHOD(OnStartupComplete)( SAFEARRAY** custom );
    STDMETHOD(OnBeginShutdown)( SAFEARRAY** custom );

    // mso::IRibbonExtensibility
    STDMETHOD(GetCustomUI)( BSTR RibbonID, BSTR* RibbonXml );

	// IPlug
    STDMETHOD(Smile)( IDispatch* ifRibbonCtrl );

private:
	HRESULT STDMETHODCALLTYPE OnDocumentOpen( word::_Document* ifDoc );
	HRESULT STDMETHODCALLTYPE OnNewDocument( word::_Document* ifDoc );

private:
	void highlight();
	void doHighlight(HWND hwnd);
	void subclassAllWindows( );
	void subclassDocWindows( word::_Document* ifDoc );



private:
	CComPtr<IDispatch> m_dispApplication;
};


OBJECT_ENTRY_AUTO(__uuidof(Plug), CPlug)
