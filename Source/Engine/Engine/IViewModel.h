#pragma once

class ColorShader;
class ID3D11Device;
class ID3D11DeviceContext;
class TextureShader;
struct XMFLOAT4X4;

class IViewModel
{
public:
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);
};