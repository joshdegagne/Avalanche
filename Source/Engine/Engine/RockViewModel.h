#pragma once

#include "ViewModel.h"
#include "GeometricPrimitive.h"
#include "CommonStates.h"

class RockObstacle;
class ITexture;
class TextureManager;

class RockViewModel : public ViewModel<RockObstacle>
{
public:
	RockViewModel(Game&);
	virtual ~RockViewModel();
	
	bool InitializeTextures(TextureManager* texMan);
	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, RockObstacle*);

private:
	ID3D11DeviceContext* context;
	ID3D11BlendState* blendState;
	unique_ptr<GeometricPrimitive> sphere;
	WCHAR*   textureFileName;
	Texture* faceTexture;
};