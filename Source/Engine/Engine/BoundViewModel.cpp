////////////////////////////////////////////////////////////////////////////////
// Filename: BoundViewModel.cpp
////////////////////////////////////////////////////////////////////////////////

#include "EntityType.h"
#include "ViewModel.cpp"
#include "BoundingBox.h"
#include "DebugConsole.h"

#include "BoundViewModel.h"


BoundViewModel::BoundViewModel() : ViewModel<BoundingBox>(EntityType::BOUNDING_BOX)
{	
	int vertexCount = 12;
	int indexCount  = 18;
	vertices = new ColorVertexType[vertexCount];
	indices  = new unsigned long[indexCount];

	vertices[0].position  = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertices[1].position  = XMFLOAT3( 0.5f, -0.5f, 0.0f);
	vertices[2].position  = XMFLOAT3(-0.5f,  0.5f, 0.0f);
	vertices[3].position  = XMFLOAT3( 0.5f,  0.5f, 0.0f);

	vertices[4].position  = XMFLOAT3( 0.0f,  0.5f,  1.0f);
	vertices[5].position  = XMFLOAT3( 0.0f, -0.5f,  0.0f);
	vertices[6].position  = XMFLOAT3( 0.0f,  0.5f,  0.0f);
	vertices[7].position  = XMFLOAT3( 0.0f, -0.5f,  1.0f);

	vertices[8].position  = XMFLOAT3(-0.5f,  0.0f,  1.0f);
	vertices[9].position  = XMFLOAT3( 0.5f,  0.0f,  0.0f);
	vertices[10].position = XMFLOAT3(-0.5f,  0.0f,  0.0f);
	vertices[11].position = XMFLOAT3( 0.5f,  0.0f,  1.0f);

	for (int i = 0; i < 4; ++i)
		vertices[i].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.9f); //green

	for (int i = 4; i < 8; ++i)
		vertices[i].color = XMFLOAT4(0.0f, 1.0f, 1.0f, 0.9f); //cyan

	for (int i = 8; i < 12; ++i)
		vertices[i].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.9f); //yellow
	
	indices[0]  = 0;
	indices[1]  = 1;
	indices[2]  = 2;
	indices[3]  = 1;
	indices[4]  = 3;
	indices[5]  = 2;

	indices[6]  = 4;
	indices[7]  = 5;
	indices[8]  = 6;
	indices[9]  = 4;
	indices[10] = 7;
	indices[11] = 5;

	indices[12] = 8;
	indices[13] = 9;
	indices[14] = 10;
	indices[15] = 8;
	indices[16] = 11;
	indices[17] = 9;

	vertexModel = new Model(vertices, vertexCount, indices, indexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

BoundViewModel::~BoundViewModel()
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

bool BoundViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
{
	bool result = vertexModel->Initialize(d3dDevice);

	if(!result) return false;

	return result;
}

bool BoundViewModel::initializeTextures(ID3D11Device* d3dDevice){
	
	return true;
}

bool BoundViewModel::RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* doesNothing, BoundingBox* entity)
{
	if (!colorShader) return false; //we were not provided with a shader

	XMFLOAT3 scaleVector       = *entity->getDimensions();
	XMMATRIX scaleMatrix       = XMMatrixScalingFromVector(XMLoadFloat3(&scaleVector));
	XMMATRIX translationMatrix = XMMatrixTranslationFromVector( XMLoadFloat3( entity->getPosition()));
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation() ) * scaleMatrix * translationMatrix);

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	vertexModel->Render(deviceContext);

	//render the game model
	bool result = colorShader->Render(deviceContext, 
										vertexModel->GetIndexCount(), 
										worldMatrix, 
										viewMatrix, 
										projectionMatrix);

	return result; 
}
