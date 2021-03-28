#pragma once
#include "ChiliWin.h"
#include "ChiliException.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "DxgiInfoManager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>
#include "ConditionalNoexcept.h"

namespace Bind
{
	class Bindable;
}

class Graphics
{
	friend class Bind::Bindable;									// need to access binable protected functions
public:
	class Exception : public ChiliException
	{
		using ChiliException::ChiliException;
	};
	class HrException : public Exception
	{
	public:
		HrException( int line,const char* file,HRESULT hr,std::vector<std::string> infoMsgs = {} ) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException( int line,const char* file,std::vector<std::string> infoMsgs = {} ) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics( HWND hWnd,int width,int height );						// initializes pDevice, pSwap, pContext, pTarget, pDSV, and ImGui
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	~Graphics() = default;
	void EndFrame();												// render screen
	void BeginFrame( float red,float green,float blue ) noexcept;	// set up frame
	void DrawIndexed( UINT count )  noxnd;							// draw indexed, non-instanced primitives
	void SetProjection( DirectX::FXMMATRIX proj ) noexcept;			// setter for projection
	DirectX::XMMATRIX GetProjection() const noexcept;				// getter for projection
	void SetCamera( DirectX::FXMMATRIX cam ) noexcept;				// setter for camera
	DirectX::XMMATRIX GetCamera() const noexcept;					// getter for camera
	void EnableImgui() noexcept;									
	void DisableImgui() noexcept;									
	bool IsImguiEnabled() const noexcept;							// get imguiEnabled
	ID3D11Device* GetDevice() { return pDevice; }
	ID3D11DeviceContext* GetContext() { return pContext; }
	ID3D11Resource* GetBackBuffer() { return pBackBuffer.Get(); }
	//ID3D11Texture2D* GetTargetTexture() { return pMyTargetTexture.Get(); }
	//ID3D11RenderTargetView* GetTarget() { return pMyTarget.Get(); }
	ID3D11RenderTargetView** GetPTarget() { return pTarget; }
	ID3D11DepthStencilView* GetDSV() { return pDSV; }
	ID3D11RenderTargetView** GetLightBuffer() { return &lightBuffer; }
	ID3D11ShaderResourceView* GetColorResource() { return pShaderView[0]; }
	ID3D11ShaderResourceView* GetNormalResource() { return pShaderView[1]; }
	ID3D11ShaderResourceView** GetShaderResources() { return pShaderView; }

private:
	DirectX::XMMATRIX projection;									// projection matrix
	DirectX::XMMATRIX camera;										// camera matrix
	bool imguiEnabled = true;										// allows for configuring objects
	static const int bufferCount = 2;
#ifndef NDEBUG
	DxgiInfoManager infoManager;									// allows for directx error macros
#endif
	ID3D11Device* pDevice;
	IDXGISwapChain* pSwap;
	ID3D11DeviceContext* pContext;

	ID3D11RenderTargetView* pTarget[bufferCount];
	ID3D11Texture2D* pTextures[3];
	ID3D11ShaderResourceView* pShaderView[bufferCount];

	ID3D11DepthStencilView* pDSV;

	ID3D11RenderTargetView* lightBuffer;
	// used in for compute shader
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	//Microsoft::WRL::ComPtr<ID3D11Texture2D> pMyTargetTexture;
	//Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pMyTarget;

};
