
#include "EntityType.h"
#include "PlayerViewModel.h"
#include "ViewModel.cpp"

PlayerViewModel::PlayerViewModel() : ViewModel<Player>(EntityType::PLAYER)
{
}

PlayerViewModel::~PlayerViewModel()
{
}

bool PlayerViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
{
	return false;
}

bool PlayerViewModel::Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader)
{
	return false;
}