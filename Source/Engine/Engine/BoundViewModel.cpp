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
	int vertexCount = 4;
	int indexCount  = 6;
	vertices = new ColorVertexType[vertexCount];
	indices  = new unsigned long[indexCount];

	vertices[0].position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertices[1].position = XMFLOAT3( 0.5f, -0.5f, 0.0f);
	vertices[2].position = XMFLOAT3(-0.5f,  0.5f, 0.0f);	
	vertices[3].position = XMFLOAT3( 0.5f,  0.5f, 0.0f);	


	for (int i = 0; i < vertexCount; ++i)
		vertices[i].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f); //red
	
	indices[0]  = 0;
	indices[1]  = 1;
	indices[2]  = 2;
	indices[3]  = 1;
	indices[4]  = 3;
	indices[5]  = 2;


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

	XMMATRIX scaleMatrix       = XMMatrixScalingFromVector(XMLoadFloat3(entity->getDimensions()));
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
