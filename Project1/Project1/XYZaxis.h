#pragma once

#include <DirectXMath.h>
#include "vertextypes.h"
#include <string>

using namespace DirectX;

class XYZaxis
{
public:
	XYZaxis();
	~XYZaxis(void);

	void Initialize();
	void Shutdown();

	
	ColorVertexType*		GetVertices();
	unsigned long*	GetIndices();
	int				GetVertexCount();
	int				GetIndexCount();


private:
	void			InitializeModel();


	ColorVertexType*		m_vertices;
	unsigned long*	m_indices;
	int				m_vertexCount;
	int				m_indexCount;

	XMFLOAT4		m_axisColor;

};

