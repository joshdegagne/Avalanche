#pragma once

#include "ViewModel.h"

class Player;
class ITexture;

class PlayerViewModel : public ViewModel<Player>
{
public:
	PlayerViewModel(float, float, WCHAR*);
	virtual ~PlayerViewModel();

	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, Player*);

private:
	WCHAR*				textureFileName;
	ITexture*			texture;
	TextureVertexType*	textureVertices;
	unsigned long*		indices;
	Model*				vertexModel;
};

