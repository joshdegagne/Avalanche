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
	vertexCount = 8;
	indexCount  = 24;
	vertices = new ColorVertexType[vertexCount];
	indices  = new unsigned long[indexCount];

	vertices[0].position = XMFLOAT3(0, 0, 0);	//Top left
	vertices[1].position = XMFLOAT3(1, 0, 0);	//Top right
	vertices[2].position = XMFLOAT3(0, 1, 0);	//Bot left
	vertices[3].position = XMFLOAT3(1, 1, 0);	//Bot right
	vertices[4].position = XMFLOAT3(0, 0, 1);	//Top left  (back)
	vertices[5].position = XMFLOAT3(1, 0, 1);	//Top right (back)
	vertices[6].position = XMFLOAT3(0, 1, 1);	//Bot left  (back)
	vertices[7].position = XMFLOAT3(1, 1, 1);	//Bot right (back)

	for (int i = 0; i < vertexCount; ++i)
		vertices[i].color = colour;
	
	indices[0]  = 0;
	indices[1]  = 1;
	indices[2]  = 0;
	indices[3]  = 2;
	indices[4]  = 3;
	indices[5]  = 1;
	indices[6]  = 3;
	indices[7]  = 2;
	indices[8]  = 4;
	indices[9]  = 5;
	indices[10] = 4;
	indices[11] = 6;
	indices[12] = 7;
	indices[13] = 5;
	indices[14] = 7;
	indices[15] = 6;
	indices[16] = 0;
	indices[17] = 4;
	indices[18] = 1;
	indices[19] = 5;
	indices[20] = 2;
	indices[21] = 6;
	indices[22] = 3;
	indices[23] = 7;
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
	//initialize vertices and textures for rendering to d3dDevice

	bool result = vertexModel->Initialize(d3dDevice);

	if(!result) return false;

	return result;
}

bool BoundViewModel::RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, BoundingBox* entity)
{
	if(!textureShader) return false; //we were not provided with a shader

	XMMATRIX scaleMatrix       = XMMatrixScalingFromVector(XMLoadFloat3(entity->getDimensions()));
	XMMATRIX translationMatrix = XMMatrixTranslationFromVector( XMLoadFloat3( &entity->getParent()->getPosition()));
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation() ) * translationMatrix * scaleMatrix);

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