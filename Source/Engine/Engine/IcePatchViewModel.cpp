
#include "Model.h"
#include "TextureShader.h"
#include "Texture.h"
#include "EntityType.h"
#include "IcePatchObstacle.h"
#include "ViewModel.cpp"

#include "IcePatchViewModel.h"

IcePatchViewModel::IcePatchViewModel() : ViewModel<IcePatchObstacle>(EntityType::ICE_PATCH)
{
	icePatchVertexModel = nullptr;
	icePatchTexture = nullptr;
}

IcePatchViewModel::~IcePatchViewModel()
{
	if(icePatchVertexModel)
		delete icePatchVertexModel;

	icePatchVertexModel = nullptr;

	if(icePatchTexture)
		delete icePatchTexture;

	icePatchTexture = nullptr;
}


bool IcePatchViewModel::InitializeVertexModels(ID3D11Device* device)
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

	icePatchVertexModel = new Model(textureVertices, vertexCount, indices, indexCount);

	success = icePatchVertexModel->Initialize(device);

	delete [] textureVertices;
	delete [] indices;

	if(!success) return false;

	//INITIALIZE TEXTURES
	//success = initializeTextures(device); // removed for new texture system

	if(!success) return false;

	return true;
}

bool IcePatchViewModel::InitializeTextures(TextureManager* texMan) 
{
	icePatchTexture = texMan->loadTexture(L"textures/tempice.dds");
	return true;
}


bool IcePatchViewModel::initializeTextures(ID3D11Device* device)
{
	int success;

	//SNOWFIELD TEXTURE
	icePatchTexture = new Texture();

	success = icePatchTexture->Initialize(device, L"textures/tempice.dds");

	if(!success) return false;

	return true;
}

bool IcePatchViewModel::RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, IcePatchObstacle* entity)
{
	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT3 positionVector = entity->getPosition();
	positionVector.z += 0.01f;
	positionVector.x -= 1.5f;
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation()));

	//SNOWFIELD MODEL RENDER
	XMFLOAT4X4 snowFieldMatrix;
	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix) * XMMatrixScaling(3.0f, entity->getLength(), 0.0f) * XMMatrixTranslationFromVector( XMLoadFloat3( &positionVector )));

	icePatchVertexModel->Render(deviceContext);

	bool result = textureShader->Render(deviceContext, 
										icePatchVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										icePatchTexture->GetTexture()); //get the texture to render

	return result; 
}