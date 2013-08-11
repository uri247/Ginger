#include "stdafx.h"
#include "dxobj.h"


STDMETHODIMP CMyID3D11Device::CreateBuffer( const D3D11_BUFFER_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Buffer **ppBuffer ) {
    m_ifInner->CreateBuffer( pDesc, pInitialData, ppBuffer );
}

STDMETHODIMP CMyID3D11Device::CreateTexture1D( const D3D11_TEXTURE1D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture1D **ppTexture1D ) {
    m_ifInner->CreateTexture1D( pDesc, pInitialData, ppTexture1D );
}

STDMETHODIMP CMyID3D11Device::CreateTexture2D( const D3D11_TEXTURE2D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture2D **ppTexture2D ) {
    m_ifInner->CreateTexture2D( pDesc, pInitialData, ppTexture2D );
}

STDMETHODIMP CMyID3D11Device::CreateTexture3D( const D3D11_TEXTURE3D_DESC *pDesc, const D3D11_SUBRESOURCE_DATA *pInitialData, ID3D11Texture3D **ppTexture3D ) {
    m_ifInner->CreateTexture3D( pDesc, pInitialData, ppTexture3D );
}

STDMETHODIMP CMyID3D11Device::CreateShaderResourceView( ID3D11Resource *pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC *pDesc, ID3D11ShaderResourceView **ppSRView ) {
    m_ifInner->CreateShaderResourceView( pResource, pDesc, ppSRView );
}

STDMETHODIMP CMyID3D11Device::CreateUnorderedAccessView( ID3D11Resource *pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC *pDesc, ID3D11UnorderedAccessView **ppUAView) {
    m_ifInner->CreateUnorderedAccessView( pResource, pDesc, ppUAView );
}

STDMETHODIMP CMyID3D11Device::CreateRenderTargetView( ID3D11Resource *pResource, const D3D11_RENDER_TARGET_VIEW_DESC *pDesc, ID3D11RenderTargetView **ppRTView) {
    m_ifInner->CreateRenderTargetView( pResource, pDesc, ppRTView );
}

STDMETHODIMP CMyID3D11Device::CreateDepthStencilView( ID3D11Resource *pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC *pDesc, ID3D11DepthStencilView **ppDepthStencilView ) {
    m_ifInner->CreateDepthStencilView( pResource, pDesc, ppDepthStencilView );
}

STDMETHODIMP CMyID3D11Device::CreateInputLayout( const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, UINT NumElements, const void *pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout **ppInputLayout) {
    m_ifInner->CreateInputLayout( pInputElementDescs, NumElements, pShaderBytecodeWithInputSignature, BytecodeLength, ppInputLayout );
}

STDMETHODIMP CMyID3D11Device::CreateVertexShader( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11VertexShader **ppVertexShader) {
    m_ifInner->CreateVertexShader( pShaderBytecode, BytecodeLength, pClassLinkage, ppVertexShader );
}

STDMETHODIMP CMyID3D11Device::CreateGeometryShader( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11GeometryShader **ppGeometryShader) {
    m_ifInner->CreateGeometryShader( pShaderBytecode, BytecodeLength, pClassLinkage, ppGeometryShader );
}

STDMETHODIMP CMyID3D11Device::CreateGeometryShaderWithStreamOutput( const void *pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY *pSODeclaration, UINT NumEntries,
	const UINT *pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage *pClassLinkage, _Out_opt_  ID3D11GeometryShader **ppGeometryShader )
{
    m_ifInner->CreateGeometryShaderWithStreamOutput( pShaderBytecode, BytecodeLength, pSODeclaration, NumEntries, pBufferStrides, NumStrides, RasterizedStream, pClassLinkage, ppGeometryShader );
}
	
STDMETHODIMP CMyID3D11Device::CreatePixelShader( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11PixelShader **ppPixelShader ) {
    m_ifInner->CreatePixelShader( pShaderBytecode, BytecodeLength, pClassLinkage, ppPixelShader );
}

STDMETHODIMP CMyID3D11Device::CreateHullShader( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11HullShader **ppHullShader ) {
    m_ifInner->CreateHullShader( pShaderBytecode, BytecodeLength, pClassLinkage, ppHullShader );
}

STDMETHODIMP CMyID3D11Device::CreateDomainShader( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11DomainShader **ppDomainShader ) {
    m_ifInner->CreateDomainShader( pShaderBytecode, BytecodeLength, pClassLinkage, ppDomainShader );
}

STDMETHODIMP CMyID3D11Device::CreateComputeShader( const void *pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage *pClassLinkage, ID3D11ComputeShader **ppComputeShader ) {
    m_ifInner->CreateComputeShader( pShaderBytecode, BytecodeLength, pClassLinkage, ppComputeShader );
}

STDMETHODIMP CMyID3D11Device::CreateClassLinkage( ID3D11ClassLinkage **ppLinkage ) {
    m_ifInner->CreateClassLinkage( );
}

STDMETHODIMP CMyID3D11Device::CreateBlendState( const D3D11_BLEND_DESC *pBlendStateDesc, ID3D11BlendState **ppBlendState) {
    m_ifInner->CreateBlendState( );
}

STDMETHODIMP CMyID3D11Device::CreateDepthStencilState( const D3D11_DEPTH_STENCIL_DESC *pDepthStencilDesc, ID3D11DepthStencilState **ppDepthStencilState ) {
    m_ifInner->CreateDepthStencilState( );
}

STDMETHODIMP CMyID3D11Device::CreateRasterizerState( const D3D11_RASTERIZER_DESC *pRasterizerDesc, ID3D11RasterizerState **ppRasterizerState ) {
    m_ifInner->CreateRasterizerState( );
}

STDMETHODIMP CMyID3D11Device::CreateSamplerState( const D3D11_SAMPLER_DESC *pSamplerDesc, ID3D11SamplerState **ppSamplerState ) {
    m_ifInner->CreateSamplerState( );
}

STDMETHODIMP CMyID3D11Device::CreateQuery( const D3D11_QUERY_DESC *pQueryDesc, ID3D11Query **ppQuery ) {
    m_ifInner->CreateQuery( );
}

STDMETHODIMP CMyID3D11Device::CreatePredicate( const D3D11_QUERY_DESC *pPredicateDesc, ID3D11Predicate **ppPredicate ) {
    m_ifInner->CreatePredicate( );
}

STDMETHODIMP CMyID3D11Device::CreateCounter( const D3D11_COUNTER_DESC *pCounterDesc, ID3D11Counter **ppCounter ) {
    m_ifInner->CreateCounter( );
}

STDMETHODIMP CMyID3D11Device::CreateDeferredContext( UINT ContextFlags, ID3D11DeviceContext **ppDeferredContext ) {
    m_ifInner->CreateDeferredContext( );
}

STDMETHODIMP CMyID3D11Device::OpenSharedResource( HANDLE hResource, REFIID ReturnedInterface, void **ppResource ) {
    m_ifInner->OpenSharedResource( );
}

STDMETHODIMP CMyID3D11Device::CheckFormatSupport( DXGI_FORMAT Format, UINT *pFormatSupport ) {
    m_ifInner->CheckFormatSupport( );
}

STDMETHODIMP CMyID3D11Device::CheckMultisampleQualityLevels( DXGI_FORMAT Format, UINT SampleCount, UINT *pNumQualityLevels ) {
    m_ifInner->CheckMultisampleQualityLevels( );
}

STDMETHOD_(void, CheckCounterInfo)( D3D11_COUNTER_INFO *pCounterInfo );        
STDMETHODIMP CMyID3D11Device::CheckCounter( const D3D11_COUNTER_DESC *pDesc, D3D11_COUNTER_TYPE *pType, UINT *pActiveCounters, LPSTR szName, UINT *pNameLength,
	LPSTR szUnits, UINT *pUnitsLength, LPSTR szDescription, UINT *pDescriptionLength ) {
	    m_ifInner->CheckCounter( );
}
	
STDMETHODIMP CMyID3D11Device::CheckFeatureSupport( D3D11_FEATURE Feature, void *pFeatureSupportData, UINT FeatureSupportDataSize ) {
    m_ifInner->CheckFeatureSupport( );
}

STDMETHODIMP CMyID3D11Device::GetPrivateData( REFGUID guid, UINT *pDataSize, void *pData ) {
    m_ifInner->GetPrivateData( );
}

STDMETHODIMP CMyID3D11Device::SetPrivateData( REFGUID guid, UINT DataSize, const void *pData ) {
    m_ifInner->SetPrivateData( );
}

STDMETHODIMP CMyID3D11Device::SetPrivateDataInterface( REFGUID guid, const IUnknown *pData ) {
    m_ifInner->SetPrivateDataInterface( );
}

STDMETHOD_(D3D_FEATURE_LEVEL, GetFeatureLevel)( );
STDMETHOD_(UINT, GetCreationFlags)();
STDMETHODIMP CMyID3D11Device::GetDeviceRemovedReason( ) {
    m_ifInner->GetDeviceRemovedReason( );
}

STDMETHOD_IMP CMyID3D11Device::void GetImmediateContext)( ID3D11DeviceContext** ppImmediateContext) {
    m_ifInner->void( );
}

STDMETHODIMP CMyID3D11Device::SetExceptionMode( UINT RaiseFlags ) {
    m_ifInner->SetExceptionMode( );
}

STDMETHOD_(UINT, GetExceptionMode)();


