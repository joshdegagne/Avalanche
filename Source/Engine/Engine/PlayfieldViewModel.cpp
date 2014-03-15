
#include "Model.h"
#include "TextureShader.h"
#include "Texture.h"
#include "EntityType.h"
#include "Playfield.h"
#include "ViewModel.cpp"

#include "PlayfieldViewModel.h"

PlayfieldViewModel::PlayfieldViewModel() : ViewModel<Playfield>(EntityType::PLAYFIELD)
{
	fieldVertexModel = nullptr;
	fieldTexture = nullptr;
}

PlayfieldViewModel::~PlayfieldViewModel()
{
	if(fieldVertexModel)
		delete fieldVertexModel;

	fieldVertexModel = nullptr;

	if(fieldTexture)
		delete fieldTexture;

	fieldTexture = nullptr;
}


bool PlayfieldViewModel::InitializeVertexModels(ID3D11Device* device)
{
	bool success;

	//SNOWFIELD MODEL
	int vertexCount = 4;
	int indexCount = 6;

	TextureVertexType* textureVertices = new TextureVertexType[vertexCount];

	unsigned long* indices = new unsigned long[indexCount];

	//Quad Face
	textureVertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	textureVertices[0].texture = XMFLOAT2(0.0f, 0.0f);
	
	textureVertices[1].position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	textureVertices[1].texture = XMFLOAT2(1.0f, 0.0f);

	textureVertices[2].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	textureVertices[2].texture = XMFLOAT2(0.0f, 1.0f);
	
	textureVertices[3].position = XMFLOAT3(1.0f, 1.0f, 0.0f); 
	textureVertices[3].texture = XMFLOAT2(1.0f, 1.0f);

	//Quad Face
	indices[0] = 0;  // Top left.
	indices[1] = 1;  // Top right.
	indices[2] = 2;  // Bottom left.
	indices[3] = 1;  // Bottom left.
	indices[4] = 3;  // Top right.  
	indices[5] = 2;  // Bottom right.

	fieldVertexModel = new Model(textureVertices, vertexCount, indices, indexCount);

	success = fieldVertexModel->Initialize(device);

	delete [] textureVertices;
	delete [] indices;

	if(!success) return false;

	//INITIALIZE TEXTURES
	success = initializeTextures(device);

	if(!success) return false;

	return true;
}

bool PlayfieldViewModel::initializeTextures(ID3D11Device* device)
{
	int success;

	//SNOWFIELD TEXTURE
	fieldTexture = new Texture();

	success = fieldTexture->Initialize(device, L"textures/tempsnow2.dds");

	if(!success) return false;

	return true;
}

bool PlayfieldViewModel::RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, Playfield* entity)
{
	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation()));

	//SNOWFIELD MODEL RENDER
	XMFLOAT4X4 snowFieldMatrix;
	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix) * XMMatrixScaling(entity->getLength(), entity->getWidth(), 0.0f));

	fieldVertexModel->Render(deviceContext);

	bool result = textureShader->Render(deviceContext, 
										fieldVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										fieldTexture->GetTexture()); //get the texture to render

	return result; 
}