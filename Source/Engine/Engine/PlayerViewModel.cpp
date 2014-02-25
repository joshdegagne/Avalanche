
#include "EntityType.h"
#include "PlayerViewModel.h"

PlayerViewModel::PlayerViewModel() : ViewModel(EntityType::PLAYER)
{
}

bool PlayerViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
{
}
