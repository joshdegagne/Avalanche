////////////////////////////////////////////////////////////////////////////////
// Filename: Model.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <d3d11.h>
#include "DirectXHelper.h"
#include "vertextype.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: Model
////////////////////////////////////////////////////////////////////////////////
class Model
{
public:
	Model();
	Model(const Model&);
	Model(ColorVertexType*, int, unsigned long*, int, D3D_PRIMITIVE_TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Model(TextureVertexType*, int, unsigned long*, int, D3D_PRIMITIVE_TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~Model();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	D3D_PRIMITIVE_TOPOLOGY primitive_topology;
	ID3D11Buffer*          vertexBuffer;
	ID3D11Buffer*          indexBuffer;

	int vertexCount;
	int indexCount;

	ColorVertexType*   colorVertices;
	TextureVertexType* textureVertices;

	unsigned long* indices;
};
