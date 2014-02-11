#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "Model.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class PrismModel : public GameModel
{
public:
	PrismModel(float height, float radius, int nFaces, XMFLOAT4 * pColors = 0);
	virtual ~PrismModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

protected:
	virtual void InitializeModel(float height, float radius, int nFaces, XMFLOAT4 * pColors);

	ColorVertexType* m_colorVertices;
	unsigned long*	m_indices;
	Model*     m_VertexModel; //vertices to put on graphics pipeline for rendering


};

