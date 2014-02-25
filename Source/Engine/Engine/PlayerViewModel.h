#pragma once

#include "ViewModel.h"

class Player;

class PlayerViewModel : ViewModel<Player>
{
public:
	PlayerViewModel();
	virtual ~PlayerViewModel();

	bool InitializeVertexModels(ID3D11Device* d3dDevice);
	bool Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);
	ID3D11ShaderResourceView* GetTexture();

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
};

