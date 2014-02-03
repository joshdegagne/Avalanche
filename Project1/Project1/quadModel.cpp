#include "Model.h"
#include "ModelUtil.h"
#include "quadmodel.h"

QuadModel::QuadModel(float lengthX, float lengthY, XMFLOAT4 * pColor) : Model()
{
	InitializeModel(lengthX, lengthY, pColor);
}

QuadModel::~QuadModel(void)
{
}


void QuadModel::InitializeModel(float lengthX, float lengthY, XMFLOAT4 * pColor)
{

	/*
	Create a quad consisting of 4 vertices and 2 triangles
	*/
	m_vertexCount = 4;
	m_indexCount = 6;

	m_colorVertices = new ColorVertexType[m_vertexCount];
	m_textureVertices = 0;

	m_indices = new unsigned long[m_indexCount];
	

	XMFLOAT4 vertexColor;
	vertexColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	if(pColor) vertexColor = *pColor;

	//Quad Face
	m_colorVertices[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, 0.0f); // Bottom left.
	m_colorVertices[0].color = vertexColor;
	
	m_colorVertices[1].position = XMFLOAT3(-lengthX/2, lengthY/2, 0.0f);  // Top left.
	m_colorVertices[1].color = vertexColor;

	m_colorVertices[2].position = XMFLOAT3(lengthX/2, -lengthY/2, 0.0f);  // Bottom right.
	m_colorVertices[2].color = vertexColor;
	
	m_colorVertices[3].position = XMFLOAT3(lengthX/2, lengthY/2, 0.0f);   // Top right.
	m_colorVertices[3].color = vertexColor;




	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.

	//Quad Face
	m_indices[0] = 0;  // Bottom left.
	m_indices[1] = 1;  // Top left.
	m_indices[2] = 2;  // Bottom right.
	m_indices[3] = 1;  // Top left.
	m_indices[4] = 3;  // Top right.  
	m_indices[5] = 2;  // Bottom right.


	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
	m_VertexModel = new ModelUtil(GetColorVertices(), GetVertexCount(), GetIndices(), GetIndexCount(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}



void QuadModel::Shutdown()
{
	if(m_colorVertices)
	{
		delete[] m_colorVertices;
		m_colorVertices = 0;
	}

	if(m_textureVertices)
	{
		delete[] m_textureVertices;
		m_textureVertices = 0;
	}

	if(m_indices)
	{
		delete[] m_indices;
		m_indices = 0;
	}

	if(m_VertexModel)
	{
		delete m_VertexModel;
		m_VertexModel = 0;
	}


}
