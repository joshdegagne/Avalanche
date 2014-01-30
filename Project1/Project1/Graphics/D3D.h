////////////////////////////////////////////////////////////////////////////////
// Filename: D3D.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _D3D_H_
#define _D3D_H_


/////////////
// LINKING //
/////////////
/*
Specify the libraries to link when using this object module. 
These libraries contain all the Direct3D functionality for setting up and drawing 3D graphics in DirectX
as well as tools to interface with the hardware on the computer to obtain information about the refresh 
rate of the monitor, the video card being used, and so forth. 
*/
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")


//////////////
// INCLUDES //
//////////////
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

#include <DirectXMath.h> //replaces XNAMath and previous math libraries since VS2010

using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: D3D
////////////////////////////////////////////////////////////////////////////////
/*
This class is our encapsulation and gateway to the DirectX 11 3D pipeline
*/
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

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	void GetProjectionMatrix(XMFLOAT4X4&);
	void GetWorldMatrix(XMFLOAT4X4&);
	void GetOrthoMatrix(XMFLOAT4X4&);
	//view matrix will be obtained from a camera object when needed

	void GetVideoCardInfo(char*, int&);


private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain; //front-back buffer swap chain
	ID3D11Device* m_device;  //the DirectX 11 device
	ID3D11DeviceContext* m_deviceContext; //the DirectX 11 device context
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;
	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT4X4 m_worldMatrix;
	XMFLOAT4X4 m_orthoMatrix;



};

#endif