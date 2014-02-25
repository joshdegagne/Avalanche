
#include "EntityType.h"
#include "PlayerViewModel.h"
#include "TextureShader.h"
#include "ViewModel.cpp"

PlayerViewModel::PlayerViewModel() : ViewModel<Player>(EntityType::PLAYER)
{
}

PlayerViewModel::~PlayerViewModel()
{
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

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	vertexModel->Render(deviceContext);

	//render the game model
	bool result = textureShader->Render(deviceContext, 
										vertexModel->GetIndexCount(), 
										GetWorldMatrix(), 
										viewMatrix, 
										projectionMatrix,
										texture->GetTexture()); //get the texture to render
	

	return result; 
}

