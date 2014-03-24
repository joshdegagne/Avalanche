#pragma once

#include "ViewModel.h"
#include "GeometricPrimitive.h"
#include "CommonStates.h"

class SmallRockObstacle;
class ITexture;
class TextureManager;

class SmallRockViewModel : public ViewModel<SmallRockObstacle>
{
public:
	SmallRockViewModel(Game&);
	virtual ~SmallRockViewModel();
	
	bool InitializeTextures(TextureManager* texMan);
	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, SmallRockObstacle*);

private:
	ID3D11DeviceContext* context;
	ID3D11BlendState* blendState;
	unique_ptr<GeometricPrimitive> sphere;
	WCHAR*   textureFileName;
	Texture* faceTexture;
};