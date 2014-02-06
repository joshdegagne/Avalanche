#include "XYZaxis.h"

XYZaxis::XYZaxis()
{

}

XYZaxis::~XYZaxis(void)
{
}

void XYZaxis::Initialize()
{
	InitializeModel();
}

void XYZaxis::InitializeModel()
{
	XMFLOAT4 X_AXIS_COLOR = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	XMFLOAT4 Y_AXIS_COLOR = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f); //yellow
	XMFLOAT4 Z_AXIS_COLOR = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f); //cyan

	m_vertexCount = 6;
	m_indexCount = 6;

	m_vertices = new ColorVertexType[m_vertexCount];
	m_indices = new unsigned long[m_indexCount];
	
	m_vertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f); // origin
	m_vertices[0].color = X_AXIS_COLOR;
	
	m_vertices[1].position = XMFLOAT3(2.0f, 0.0f, 0.0f);  // positive X.
	m_vertices[1].color = X_AXIS_COLOR;

	m_vertices[2].position = XMFLOAT3(0.0f, 0.0f, 0.0f); // origin
	m_vertices[2].color = Y_AXIS_COLOR;

	m_vertices[3].position = XMFLOAT3(0.0f, 2.0f, 0.0f);  // postive Y.
	m_vertices[3].color = Y_AXIS_COLOR;
	
	m_vertices[4].position = XMFLOAT3(0.0f, 0.0f, 0.0f); // origin
	m_vertices[4].color = Z_AXIS_COLOR;

	m_vertices[5].position = XMFLOAT3(0.0f, 0.0f, 2.0f);   // positive Z.
	m_vertices[5].color = Z_AXIS_COLOR;
	
	
	// Load the index array with data.
	m_indices[0] = 0;  // origin.
	m_indices[1] = 1;  // X.
	m_indices[2] = 2;  // origin.
	m_indices[3] = 3;  // Y.
	m_indices[4] = 4;  // origin.  
	m_indices[5] = 5;  // Z.

}



void XYZaxis::Shutdown()
{
	if(m_vertices)
	{
		delete[] m_vertices;
		m_vertices = 0;
	}

	if(m_indices)
	{
		delete[] m_indices;
		m_indices = 0;
	}


}






ColorVertexType* XYZaxis::GetVertices()
{
	return m_vertices;
}

unsigned long* XYZaxis::GetIndices()
{
	return m_indices;
}

int XYZaxis::GetVertexCount() {
	return m_vertexCount;
}

int XYZaxis::GetIndexCount() {
	return m_indexCount;
}

