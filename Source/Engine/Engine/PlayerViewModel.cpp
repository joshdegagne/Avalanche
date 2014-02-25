
#include "EntityType.h"
#include "TextureShader.h"
#include "ViewModel.cpp"
#include "Player.h"

#include "PlayerViewModel.h"

PlayerViewModel::PlayerViewModel(float lengthX, float lengthY, WCHAR* aTextureFileName) : ViewModel<Player>(EntityType::PLAYER)
{
	/*
	Create a quad consisting of 4 vertices and 2 triangles
	*/
	int vertexCount = 4;
	int indexCount = 6;

	textureVertices = new TextureVertexType[vertexCount];

	indices = new unsigned long[indexCount];

	//potentially dangerous, we should probably make a copy of the string and
	//release it ourselves later
	textureFileName = aTextureFileName;

	//Quad Face
	textureVertices[0].position = XMFLOAT3(-lengthX/2, -lengthY/2, 0.0f); // Top left.
	textureVertices[0].texture = XMFLOAT2(0.0f, 0.0f);
	
	textureVertices[1].position = XMFLOAT3(-lengthX/2, lengthY/2, 0.0f);  // Bottom left.
	textureVertices[1].texture = XMFLOAT2(0.0f, 1.0f);

	textureVertices[2].position = XMFLOAT3(lengthX/2, -lengthY/2, 0.0f);  // Top right.
	textureVertices[2].texture = XMFLOAT2(1.0f, 0.0f);
	
	textureVertices[3].position = XMFLOAT3(lengthX/2, lengthY/2, 0.0f);   // Bottom right.
	textureVertices[3].texture = XMFLOAT2(1.0f, 1.0f);

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
	vertexModel = new Model(textureVertices, vertexCount, indices, indexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

PlayerViewModel::~PlayerViewModel()
{
		if(textureVertices)
	{
		delete[] textureVertices;
		textureVertices = 0;
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

	// Release the texture objects.
	if(texture)
	{
		delete texture;
		texture = 0;
	}
}

bool PlayerViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
{
	//initialize vertices and textures for rendering to d3dDevice

	bool result = vertexModel->Initialize(d3dDevice);

	if(!result) return false;

	result = initializeTextures(d3dDevice);

	return result;
}

bool PlayerViewModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	texture = new Texture;
	if(!texture)
	{
		return false;
	}
	// Initialize the body texture object.
	result = texture->Initialize(d3dDevice, textureFileName);
	if(!result)
	{
	return false;
}

	return true;
}

bool PlayerViewModel::RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, Player* entity)
{
	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation() ) * XMMatrixTranslationFromVector( XMLoadFloat2( &entity->getPos() )));

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	vertexModel->Render(deviceContext);

	//render the game model
	bool result = textureShader->Render(deviceContext, 
										vertexModel->GetIndexCount(), 
										worldMatrix, 
										viewMatrix, 
										projectionMatrix,
										texture->GetTexture()); //get the texture to render
	

	return result; 
}

