#pragma once

#include "DirectXHelper.h"
#include <d3d11.h>
#include "TextureManager.h"

using namespace DirectX;

class ColorShader;
class TextureShader;
class TextureManager;

class IViewModel
{
public:
	virtual ~IViewModel() {};
	//virtual bool InitializeTextures(TextureManager* texMan) = 0;
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice) { return false; };
	virtual bool Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader) = 0;
};