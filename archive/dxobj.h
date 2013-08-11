#pragma once


class ATL_NO_VTABLE CMyID3D11Device
    : public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
    , public ID3D11Device
{
    BEGIN_COM_MAP(CMyID3D11Device)
        COM_INTERFACE_ENTRY(ID3D11Device)
    END_COM_MAP()


public:
	void setInner( ID3D11Device* ifDevice ) {
		m_ifDevice = ifDevice;
	}

	//
	// ID3D11Device
	//

    STDMETHOD(CreateBuffer)( const D3D11_BUFFER_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Buffer **ppBuffer );        
    STDMETHOD(CreateTexture1D)( const D3D11_TEXTURE1D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture1D **ppTexture1D );
    STDMETHOD(CreateTexture2D)( const D3D11_TEXTURE2D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D **ppTexture2D );        
    STDMETHOD(CreateTexture3D)( const D3D11_TEXTURE3D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture3D **ppTexture3D );
    STDMETHOD(CreateShaderResourceView)( ID3D11Resource *pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D11ShaderResourceView **ppSRView );        
    STDMETHOD(CreateUnorderedAccessView)( ID3D11Resource *pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc, ID3D11UnorderedAccessView **ppUAView);
    STDMETHOD(CreateRenderTargetView)( ID3D11Resource *pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView **ppRTView);        
    STDMETHOD(CreateDepthStencilView)( ID3D11Resource *pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc, ID3D11DepthStencilView **ppDepthStencilView );
    STDMETHOD(CreateInputLayout)( const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, UINT NumElements, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout **ppInputLayout);        
    STDMETHOD(CreateVertexShader)( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader);        
    STDMETHOD(CreateGeometryShader)( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader);
    STDMETHOD(CreateGeometryShaderWithStreamOutput)( const void *pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries,
		const UINT *pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage *pClassLinkage, _Out_opt_  ID3D11GeometryShader **ppGeometryShader );
    STDMETHOD(CreatePixelShader)( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader );
    STDMETHOD(CreateHullShader)( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11HullShader **ppHullShader );
    STDMETHOD(CreateDomainShader)( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11DomainShader **ppDomainShader );
    STDMETHOD(CreateComputeShader)( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11ComputeShader **ppComputeShader );
    STDMETHOD(CreateClassLinkage)( ID3D11ClassLinkage **ppLinkage );        
    STDMETHOD(CreateBlendState)( const D3D11_BLEND_DESC *pBlendStateDesc, ID3D11BlendState **ppBlendState);        
    STDMETHOD(CreateDepthStencilState)( const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc, ID3D11DepthStencilState **ppDepthStencilState );        
    STDMETHOD(CreateRasterizerState)( const D3D11_RASTERIZER_DESC *pRasterizerDesc, ID3D11RasterizerState **ppRasterizerState );        
    STDMETHOD(CreateSamplerState)( const D3D11_SAMPLER_DESC *pSamplerDesc, ID3D11SamplerState **ppSamplerState );        
    STDMETHOD(CreateQuery)( const D3D11_QUERY_DESC *pQueryDesc, ID3D11Query **ppQuery );        
    STDMETHOD(CreatePredicate)( const D3D11_QUERY_DESC *pPredicateDesc, ID3D11Predicate **ppPredicate );
    STDMETHOD(CreateCounter)( const D3D11_COUNTER_DESC *pCounterDesc, ID3D11Counter **ppCounter );
    STDMETHOD(CreateDeferredContext)( UINT ContextFlags, ID3D11DeviceContext **ppDeferredContext );
    STDMETHOD(OpenSharedResource)( HANDLE hResource, REFIID ReturnedInterface, void **ppResource );
    STDMETHOD(CheckFormatSupport)( DXGI_FORMAT Format, UINT *pFormatSupport );
    STDMETHOD(CheckMultisampleQualityLevels)( DXGI_FORMAT Format, UINT SampleCount, UINT *pNumQualityLevels );
    STDMETHOD_(void, CheckCounterInfo)( D3D11_COUNTER_INFO *pCounterInfo );        
    STDMETHOD(CheckCounter)( const D3D11_COUNTER_DESC *pDesc, D3D11_COUNTER_TYPE *pType, UINT *pActiveCounters, LPSTR szName, UINT *pNameLength,
		LPSTR szUnits, UINT *pUnitsLength, LPSTR szDescription, UINT *pDescriptionLength );
    STDMETHOD(CheckFeatureSupport)( D3D11_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize );
    STDMETHOD(GetPrivateData)( REFGUID guid, UINT *pDataSize, void *pData );        
    STDMETHOD(SetPrivateData)( REFGUID guid, UINT DataSize, const void *pData );        
    STDMETHOD(SetPrivateDataInterface)( REFGUID guid, const IUnknown *pData );        
    STDMETHOD_(D3D_FEATURE_LEVEL, GetFeatureLevel)( );
    STDMETHOD_(UINT, GetCreationFlags)();
    STDMETHOD(GetDeviceRemovedReason)( );        
    STDMETHOD_(void, GetImmediateContext)( ID3D11DeviceContext** ppImmediateContext);
	STDMETHOD(SetExceptionMode)( UINT RaiseFlags );
    STDMETHOD_(UINT, GetExceptionMode)();

private:
	ATL::CComPtr<ID3D11Device> m_ifInner;

};