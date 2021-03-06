#pragma once

#include "ViewModel.h"

class Game;
class Model;
class Playfield;
class TextureManager;

class PlayfieldViewModel : public ViewModel<Playfield>
{
public:
	PlayfieldViewModel();
	~PlayfieldViewModel();
	
	bool InitializeTextures(TextureManager* texMan);
	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, Playfield* entity);

	Model*		fieldVertexModel;
	ITexture*	fieldTexture;
	Model*		avalancheVertexModel;
	ITexture*	avalancheTexture;
	Model*		avalancheSideVertexModel;
	ITexture*	avalancheSideTexture;
};