#pragma once

#include "ViewModel.h"

class SmallRockObstacle;
class ITexture;
class TextureManager;

class SmallRockViewModel : public ViewModel<SmallRockObstacle>
{
public:
	SmallRockViewModel();
	virtual ~SmallRockViewModel();
	
	bool InitializeTextures(TextureManager* texMan);
	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, SmallRockObstacle*);

private:
	static const int NUMBER_OF_TEXTURES = 3;

	WCHAR*   textureFileName;
	Texture* faceTexture;
	Model*   vertexModel;
};