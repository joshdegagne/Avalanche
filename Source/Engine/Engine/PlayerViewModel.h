#pragma once

#include "ViewModel.h"

class Player;
class ITexture;

class PlayerViewModel : ViewModel<Player>
{
public:
	PlayerViewModel();
	virtual ~PlayerViewModel();

	bool InitializeVertexModels(ID3D11Device* d3dDevice);
	ID3D11ShaderResourceView* GetTexture();

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, Player*);

private:
	ITexture* texture;
};

