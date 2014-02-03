////////////////////////////////////////////////////////////////////////////////
// Filename: ModelHelper.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELHELPER_H_
#define _MODELHELPER_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>

#include "vertextypes.h"

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelHelper
////////////////////////////////////////////////////////////////////////////////
class ModelHelper
{
public:
	ModelHelper();
	ModelHelper(const ModelHelper&);
	ModelHelper(ColorVertexType*, int, unsigned long*, int, D3D_PRIMITIVE_TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ModelHelper(TextureVertexType*, int, unsigned long*, int, D3D_PRIMITIVE_TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	~ModelHelper();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	D3D_PRIMITIVE_TOPOLOGY m_primitive_topology;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	ColorVertexType* m_colorVertices;
	TextureVertexType* m_textureVertices;
	unsigned long* m_indices;
};

#endif