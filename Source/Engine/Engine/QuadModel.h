////////////////////////////////////////////////////////////////////////////////
// Filename: QuadModel.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "vertextype.h"
#include "Model.h"
#include "gamemodel.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class name: QuadModel
////////////////////////////////////////////////////////////////////////////////
class QuadModel : public GameModel
	//This model represents a quad made up of two trianges.
	//One of lengthX, lengthY, or lengthZ must be 0;
{
public:
	QuadModel(float lengthX, float lengthY, XMFLOAT4 * pColor = 0);
	virtual ~QuadModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

protected:
	virtual void InitializeModel(float lengthX, float lengthY, XMFLOAT4 * pColor);
	
	ColorVertexType* colorVertices;
	unsigned long*	 indices;
	Model*           vertexModel; //vertices to put on graphics pipeline for rendering


};

