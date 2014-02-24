#include "gamemodel.h"
#include "Model.h"
#include "quadmodel.h"
#include "ColorShader.h"
#include "TextureShader.h"

QuadModel::QuadModel(float lengthX, float lengthY, XMFLOAT4 * pColor) : GameModel()
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
	int vertexCount = 4;
	int indexCount = 6;

	colorVertices = new ColorVertexType[vertexCount];
	indices = new unsigned long[indexCount];
	

	XMFLOAT4 vertexColor;
	vertexColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	if(pColor) vertexColor = *pColor;

	//Quad Face
	colorVertices[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, 0.0f); // Top left.
	colorVertices[0].color = vertexColor;
	
	colorVertices[1].position = XMFLOAT3(-lengthX/2, lengthY/2, 0.0f);  // Bottom left.
	colorVertices[1].color = vertexColor;

	colorVertices[2].position = XMFLOAT3(lengthX/2, -lengthY/2, 0.0f);  // Top right.
	colorVertices[2].color = vertexColor;
	
	colorVertices[3].position = XMFLOAT3(lengthX/2, lengthY/2, 0.0f);   // Bottom right.
	colorVertices[3].color = vertexColor;

	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.

	//Quad Face
	indices[0] = 0;  // Top left.
	indices[1] = 2;  // Top right.
	indices[2] = 1;  // Bottom left.
	indices[3] = 1;  // Bottom left.
	indices[4] = 2;  // Top right.  
	indices[5] = 3;  // Bottom right.


	//Create the ModelClass object that will be used to deliver these vertices to the graphics pipeline
	vertexModel = new Model(colorVertices, vertexCount, indices, indexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

bool QuadModel::InitializeVertexModels(ID3D11Device* d3dDevice){
	//subclasses who have vertices are expected to overide this method
	return vertexModel->Initialize(d3dDevice);

}

bool QuadModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader){
	
	if(!colorShader) return false; //we were not provided with a shader

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	 vertexModel->Render(deviceContext);

	 //render the game model
	 bool result = colorShader->Render(deviceContext, 
		                                  vertexModel->GetIndexCount(), 
								          GetWorldMatrix(), 
								          viewMatrix, 
								          projectionMatrix);
	
	return result; 

}


void QuadModel::Shutdown()
{
	if(colorVertices)
	{
		delete[] colorVertices;
		colorVertices = 0;
	}



	if(indices)
	{
		delete[] indices;
		indices = 0;
	}

	if(vertexModel)
	{
		delete vertexModel;
		vertexModel = 0;
	}


}
