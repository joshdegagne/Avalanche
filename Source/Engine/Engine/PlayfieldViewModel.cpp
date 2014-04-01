
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
	avalancheVertexModel = nullptr;
}

PlayfieldViewModel::~PlayfieldViewModel()
{
	if(fieldVertexModel)
		delete fieldVertexModel;

	fieldVertexModel = nullptr;

	if(fieldTexture)
		delete fieldTexture;

	fieldTexture = nullptr;

	if(avalancheVertexModel)
		delete avalancheVertexModel;

	avalancheVertexModel = nullptr;
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
	textureVertices[0].texture = XMFLOAT2(0.0f, 0.4f);
	
	textureVertices[1].position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	textureVertices[1].texture = XMFLOAT2(1.0f, 0.4f);

	textureVertices[2].position = XMFLOAT3(0.0f, 1.0f, 0.0f);
	textureVertices[2].texture = XMFLOAT2(0.0f, 0.6f);
	
	textureVertices[3].position = XMFLOAT3(1.0f, 1.0f, 0.0f); 
	textureVertices[3].texture = XMFLOAT2(1.0f, 0.6f);

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

	//AVALANCHE MODEL
	vertexCount = 6;
	indexCount = 12;

	textureVertices = new TextureVertexType[vertexCount];

	indices = new unsigned long[indexCount];

	//Quad Face
	textureVertices[0].position = XMFLOAT3(-12.0f, 0.0f, 4.0f);
	textureVertices[0].texture = XMFLOAT2(0.0f, 0.0f);
	
	textureVertices[1].position = XMFLOAT3(-12.0f, 1.0f, 4.0f);
	textureVertices[1].texture = XMFLOAT2(1.0f, 0.0f);

	textureVertices[2].position = XMFLOAT3(-1.0f, 0.0f, 1.4f);
	textureVertices[2].texture = XMFLOAT2(0.0f, 3.0f);
	
	textureVertices[3].position = XMFLOAT3(-1.0f, 1.0f, 1.4f); 
	textureVertices[3].texture = XMFLOAT2(1.0f, 3.0f);

	textureVertices[4].position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	textureVertices[4].texture = XMFLOAT2(0.0f, 3.6f);
	
	textureVertices[5].position = XMFLOAT3(1.0f, 1.0f, 0.0f); 
	textureVertices[5].texture = XMFLOAT2(1.0f, 3.6f);

	//Quad Face
	indices[0] = 0;  // Top left.
	indices[1] = 3;  // Top right.
	indices[2] = 1;  // Bottom left.
	indices[3] = 0;  // Bottom left.
	indices[4] = 2;  // Top right.  
	indices[5] = 3;  // Bottom right.

	indices[6] = 2;
	indices[7] = 5;  
	indices[8] = 3;
	indices[9] = 2;
	indices[10] = 4;  
	indices[11] = 5;

	avalancheVertexModel = new Model(textureVertices, vertexCount, indices, indexCount);

	success = avalancheVertexModel->Initialize(device);

	delete [] textureVertices;
	delete [] indices;

	if(!success) return false;

	//AVALANCHE MODEL
	vertexCount = 4;
	indexCount = 12;

	textureVertices = new TextureVertexType[vertexCount];

	indices = new unsigned long[indexCount];

	//Quad Face
	textureVertices[0].position = XMFLOAT3(-12.0f, 6.0f, 4.0f);
	textureVertices[0].texture = XMFLOAT2(0.0f, 0.0f);

	textureVertices[1].position = XMFLOAT3(-12.0f, 6.0f, 0.0f);
	textureVertices[1].texture = XMFLOAT2(1.0f, 0.0f);
	
	textureVertices[2].position = XMFLOAT3(-1.0f, 6.0f, 1.4f); 
	textureVertices[2].texture = XMFLOAT2(0.0f, 1.0f);
	
	textureVertices[3].position = XMFLOAT3(1.0f, 6.0f, 0.0f); 
	textureVertices[3].texture = XMFLOAT2(1.0f, 1.0f);

	//Quad Face
	indices[0] = 0;  // Top left.
	indices[1] = 3;  // Top right.
	indices[2] = 1;  // Bottom left.
	indices[3] = 0;  // Bottom left.
	indices[4] = 2;  // Top right.  
	indices[5] = 3;  // Bottom right.

	avalancheSideVertexModel = new Model(textureVertices, vertexCount, indices, indexCount);

	success = avalancheSideVertexModel->Initialize(device);

	delete [] textureVertices;
	delete [] indices;

	if(!success) return false;

	//INITIALIZE TEXTURES
	//success = initializeTextures(device); // removed for new texture system

	if(!success) return false;

	return true;
}

bool PlayfieldViewModel::InitializeTextures(TextureManager* texMan) 
{
	fieldTexture = texMan->loadTexture(L"textures/tiledsnow.dds");

	SpriteTexture* sprite = texMan->loadSpriteTexture(L"textures/avalanche_frames.png", 100);
	sprite->setFrameRate(0.02);
	avalancheTexture = sprite;

	avalancheSideTexture = texMan->loadTexture(L"textures/avalanche_side.png");

	return true;
}

// deprecated
bool PlayfieldViewModel::initializeTextures(ID3D11Device* device)
{
	int success;

	//SNOWFIELD TEXTURE
	fieldTexture = new Texture();

	success = fieldTexture->Initialize(device, L"textures/tiledsnow.dds");

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
	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix) * XMMatrixTranslation(-entity->getScrollAmount(), 0.0f, 0.0f) * XMMatrixScaling(entity->getLength(), entity->getWidth(), 0.0f));

	fieldVertexModel->Render(deviceContext);

	bool result = textureShader->Render(deviceContext, 
										fieldVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										fieldTexture->GetTexture()); //get the texture to render

	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix) * XMMatrixTranslation(-entity->getScrollAmount() + 1.0f, 0.0f, 0.0f) * XMMatrixScaling(entity->getLength(), entity->getWidth(), 0.0f));

	fieldVertexModel->Render(deviceContext);

	result = textureShader->Render(deviceContext, 
										fieldVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										fieldTexture->GetTexture()); //get the texture to render

	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix) * XMMatrixTranslation(-entity->getScrollAmount() - 1.0f, 0.0f, 0.0f) * XMMatrixScaling(entity->getLength(), entity->getWidth(), 0.0f));

	fieldVertexModel->Render(deviceContext);

	result = textureShader->Render(deviceContext, 
										fieldVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										fieldTexture->GetTexture()); //get the texture to render

	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix) * XMMatrixScaling(1.0f, entity->getWidth(), 1.0f));

	avalancheVertexModel->Render(deviceContext);

	result = textureShader->Render(deviceContext, 
										avalancheVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										avalancheTexture->GetTexture()); //get the texture to render

	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix));

	avalancheSideVertexModel->Render(deviceContext);

	result = textureShader->Render(deviceContext, 
										avalancheVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										avalancheSideTexture->GetTexture()); //get the texture to render

	return result; 
}