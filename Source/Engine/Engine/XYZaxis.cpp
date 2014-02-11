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

	vertexCount = 6;
	indexCount = 6;

	vertices = new ColorVertexType[vertexCount];
	indices = new unsigned long[indexCount];
	
	vertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f); // origin
	vertices[0].color = X_AXIS_COLOR;
	
	vertices[1].position = XMFLOAT3(2.0f, 0.0f, 0.0f);  // positive X.
	vertices[1].color = X_AXIS_COLOR;

	vertices[2].position = XMFLOAT3(0.0f, 0.0f, 0.0f); // origin
	vertices[2].color = Y_AXIS_COLOR;

	vertices[3].position = XMFLOAT3(0.0f, 2.0f, 0.0f);  // postive Y.
	vertices[3].color = Y_AXIS_COLOR;
	
	vertices[4].position = XMFLOAT3(0.0f, 0.0f, 0.0f); // origin
	vertices[4].color = Z_AXIS_COLOR;

	vertices[5].position = XMFLOAT3(0.0f, 0.0f, 2.0f);   // positive Z.
	vertices[5].color = Z_AXIS_COLOR;
	
	
	// Load the index array with data.
	indices[0] = 0;  // origin.
	indices[1] = 1;  // X.
	indices[2] = 2;  // origin.
	indices[3] = 3;  // Y.
	indices[4] = 4;  // origin.  
	indices[5] = 5;  // Z.

}



void XYZaxis::Shutdown()
{
	if(vertices)
	{
		delete[] vertices;
		vertices = 0;
	}

	if(indices)
	{
		delete[] indices;
		indices = 0;
	}


}






ColorVertexType* XYZaxis::GetVertices()
{
	return vertices;
}

unsigned long* XYZaxis::GetIndices()
{
	return indices;
}

int XYZaxis::GetVertexCount() {
	return vertexCount;
}

int XYZaxis::GetIndexCount() {
	return indexCount;
}

