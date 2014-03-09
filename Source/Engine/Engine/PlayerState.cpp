#include "PlayerState.h"

PlayerState::PlayerState(Player& p) 
	        : player(p), timer(new Timer()) {}