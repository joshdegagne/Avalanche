#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "Model.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class CubeModel : public GameModel
{
public:
	CubeModel(float lengthX, float lengthY, float lengthZ, XMFLOAT4 * pColors = 0);
	virtual ~CubeModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

protected:
	virtual void InitializeModel(float lengthX, float lengthY, float lengthZ, XMFLOAT4 * pColors);

	ColorVertexType* m_colorVertices;
	unsigned long*	 m_indices;
	Model*           m_VertexModel; //vertices to put on graphics pipeline for rendering


};

