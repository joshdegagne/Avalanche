
#include "EntityType.h"
#include "TextureShader.h"
#include "ViewModel.cpp"
#include "Player.h"
#include "DebugConsole.h"
#include "Game.h"
#include "Camera.h"
#include "DebugDefinitions.h"

#include "PlayerViewModel.h"

const float WIDTH	= 0.9f;
const float HEIGHT	= 2.0f;

//WCHAR* TEXTURE = L"textures/iceclimberhead.dds";

PlayerViewModel::PlayerViewModel(Game& game) : ViewModel<Player>(EntityType::PLAYER)
{

	orientRotateY(-0.1f);
	orientRotateZ(0.2f);

	/*
	Create a quad consisting of 4 vertices and 2 triangles
	*/
	int vertexCount = 4;
	int indexCount = 6;

	textureVertices = new TextureVertexType[vertexCount];

	indices = new unsigned long[indexCount];

	//potentially dangerous, we should probably make a copy of the string and
	//release it ourselves later
	//textureFileName = TEXTURE;

	//Quad Face
	textureVertices[0].position = XMFLOAT3(0.0f, -WIDTH/2, 0.0f); // Top left.
	textureVertices[0].texture = XMFLOAT2(1.0f, 1.0f);
	
	textureVertices[1].position = XMFLOAT3(0.0f, WIDTH/2, 0.0f);  // Bottom left.
	textureVertices[1].texture = XMFLOAT2(0.0f, 1.0f);

	textureVertices[2].position = XMFLOAT3(0.0f, -WIDTH/2, HEIGHT);  // Top right.
	textureVertices[2].texture = XMFLOAT2(1.0f, 0.0f);
	
	textureVertices[3].position = XMFLOAT3(0.0f, WIDTH/2, HEIGHT);   // Bottom right.
	textureVertices[3].texture = XMFLOAT2(0.0f, 0.0f);

	// Load the index array with data.
	// Two triangles per face. The directions are consistent
	// With back-face culling in a left-hand co-ordinate system.

	//Quad Face
	indices[0] = 0;  // Top left.
	indices[1] = 1;  // Top right.
	indices[2] = 2;  // Bottom left.
	indices[3] = 1;  // Bottom left.
	indices[4] = 3;  // Top right.  
	indices[5] = 2;  // Bottom right.

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
	//if(textures)
	//{
	//	delete [] textures;
	//	textures = 0;
	//}
	}

bool PlayerViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
{

	//SHADOW MODEL
	int vertexCount = 4;
	int indexCount = 6;

	TextureVertexType* textureVertices = new TextureVertexType[vertexCount];
	unsigned long* indices = new unsigned long[indexCount];

	//Quad Face
	textureVertices[0].position = XMFLOAT3(-WIDTH * 0.4f, -WIDTH * 0.4f, 0.01f); // Top left.
	textureVertices[0].texture = XMFLOAT2(1.0f, 1.0f);
	
	textureVertices[1].position = XMFLOAT3(-WIDTH * 0.4f, WIDTH * 0.4f, 0.01f);  // Bottom left.
	textureVertices[1].texture = XMFLOAT2(0.0f, 1.0f);

	textureVertices[2].position = XMFLOAT3(WIDTH * 0.4f, -WIDTH * 0.4f, 0.01f);  // Top right.
	textureVertices[2].texture = XMFLOAT2(1.0f, 0.0f);
	
	textureVertices[3].position = XMFLOAT3(WIDTH * 0.4f, WIDTH * 0.4f, 0.01f);   // Bottom right.
	textureVertices[3].texture = XMFLOAT2(0.0f, 0.0f);

	//initialize vertices and textures for rendering to d3dDevice
	indices[0] = 0;  // Top left.
	indices[1] = 2;  // Top right.
	indices[2] = 1;  // Bottom left.
	indices[3] = 1;  // Bottom left.
	indices[4] = 2;  // Top right.  
	indices[5] = 3;  // Bottom right.

	shadowVertexModel = new Model(textureVertices, vertexCount, indices, indexCount);

	bool result = shadowVertexModel->Initialize(d3dDevice);
	if(!result) return false;

	delete [] textureVertices;
	delete [] indices;


	result = vertexModel->Initialize(d3dDevice);

	if(!result) return false;

	//result = initializeTextures(d3dDevice); // removed for new texturing system

	return result;
}

bool PlayerViewModel::InitializeTextures(TextureManager* texMan) 
{
	
	//if (!(textures[0] = texMan->loadTexture(L"textures/player_red.dds")))
	if (!(textures[0] = texMan->loadSpriteTexture(L"textures/player_red_running.png", 100)))
	//	return false;
		return false;

	if (!(textures[1] = texMan->loadTexture(L"textures/player_purple.dds")))
		return false;

	if (!(textures[2] = texMan->loadTexture(L"textures/player_green.dds")))
		return false;

	if (!(textures[3] = texMan->loadTexture(L"textures/player_yellow.dds")))
		return false;

	if (!(shadowTexture = texMan->loadTexture(L"textures/shadow.dds")))
		return false;

	
	// pass in the intended width of each cell
	
	return true;

}

// DEPRECATED!
bool PlayerViewModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	for(int i = 0; i < 4; ++i)
	{
		textures[i] = new Texture;
		if(!textures)
		return false;
	
	}

	shadowTexture = new Texture;
	if(!shadowTexture)
		return false;

	// Initialize the body texture object.
	result = textures[0]->Initialize(d3dDevice, L"textures/player_red.dds");
	if(!result)
		return false;

	result = textures[1]->Initialize(d3dDevice, L"textures/player_purple.dds");
	if(!result)
		return false;

	result = textures[2]->Initialize(d3dDevice, L"textures/player_green.dds");
	if(!result)
		return false;

	result = textures[3]->Initialize(d3dDevice, L"textures/player_yellow.dds");
	if(!result)
		return false;

	result = shadowTexture->Initialize(d3dDevice, L"textures/shadow.dds");
	if(!result)
		return false;

	return true;
}

bool PlayerViewModel::RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, Player* entity)
{
	bool result = true;

	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation() ) * XMMatrixTranslationFromVector( XMLoadFloat3( &entity->getPosition() )));



	XMFLOAT3 shadowPosition = entity->getPosition();
	shadowPosition.z = 0.0f;
	
	XMFLOAT4X4 shadowMatrix;
	XMStoreFloat4x4(&shadowMatrix, XMMatrixTranslationFromVector( XMLoadFloat3( &shadowPosition )));

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	vertexModel->Render(deviceContext);

	//render the game model
	result = textureShader->Render(deviceContext, 
										vertexModel->GetIndexCount(), 
										worldMatrix, 
										viewMatrix, 
										projectionMatrix,
										textures[entity->getPlayerNum()]->GetTexture()); //get the texture to render... size 12 for some reason?


	//RENDER SHADOW
	shadowVertexModel->Render(deviceContext);

	result = textureShader->Render(deviceContext, 
										shadowVertexModel->GetIndexCount(), 
										shadowMatrix, 
										viewMatrix, 
										projectionMatrix,
										shadowTexture->GetTexture()); //get the texture to render

	return result; 
}

