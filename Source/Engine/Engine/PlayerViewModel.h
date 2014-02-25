#pragma once

#include "ViewModel.h"

class Player;

class PlayerViewModel : ViewModel<Player>
{
public:
	PlayerViewModel();

	bool InitializeVertexModels(ID3D11Device* d3dDevice);
};

