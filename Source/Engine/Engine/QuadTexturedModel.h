////////////////////////////////////////////////////////////////////////////////
// Filename: QuadTexturedModel.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "vertextype.h"
#include "Texture.h"
#include "Model.h"
#include "gamemodel.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class name: QuadTexturedModel
////////////////////////////////////////////////////////////////////////////////
class QuadTexturedModel : public GameModel
	//This model represents a quad made up of two trianges.
	//One of lengthX, lengthY, or lengthZ must be 0;
{
public:
	QuadTexturedModel(float lengthX, float lengthY, WCHAR* aTextureFileName);
	virtual ~QuadTexturedModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
    virtual bool initializeTextures(ID3D11Device* d3dDevice);
	virtual ID3D11ShaderResourceView* GetTexture();
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

protected:
	virtual void InitializeModel(float lengthX, float lengthY, WCHAR* aTextureFileName);

private:
	WCHAR*   textureFileName;
	Texture* quadTexture;

	TextureVertexType* textureVertices;
	unsigned long*	   indices;
	Model*             vertexModel; //vertices to put on graphics pipeline for rendering

};
