////////////////////////////////////////////////////////////////////////////////
// Filename: D3D.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "DirectXHelper.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: D3D
////////////////////////////////////////////////////////////////////////////////
class D3D
{
public:
	D3D();
	D3D(const D3D&);
	~D3D();

	bool Initialize(int, int, bool, HWND, bool, float, float); //initialized the DirectX object/pipeline
	void Shutdown(); //release resources
	
	void BeginScene(float, float, float, float); //clear back buffer and depth  and get it ready to render on
	void EndScene(); //present back buffer to the screen

	ID3D11Device*        GetDevice();
	ID3D11DeviceContext* GetContext();
	ID3D11BlendState*    GetBlendState();

	void GetProjectionMatrix(XMFLOAT4X4&);
	void GetWorldMatrix(XMFLOAT4X4&);
	void GetOrthoMatrix(XMFLOAT4X4&);
	//view matrix will be obtained from a camera object when needed

	void GetVideoCardInfo(char*, int&);

	ID3D11RenderTargetView* getRenderTargetView();
	ID3D11DepthStencilView* getDepthStencilView();
	IDXGISwapChain*			getSwapChain();


private:
	bool vsync_enabled;
	int  videoCardMemory;
	char videoCardDescription[128];

	IDXGISwapChain*          swapChain; //front-back buffer swap chain
	ID3D11Device*            device;  //the DirectX 11 device
	ID3D11DeviceContext*     deviceContext; //the DirectX 11 device context
	ID3D11RenderTargetView*  renderTargetView;
	ID3D11Texture2D*         depthStencilBuffer;
	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilView*  depthStencilView;
	ID3D11RasterizerState*   rasterState;

	XMFLOAT4X4 projectionMatrix;
	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 orthoMatrix;
	
	ID3D11BlendState* alphaEnableBlendingState;


};