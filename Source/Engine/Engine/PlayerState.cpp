#include "PlayerState.h"

PlayerState::PlayerState(Player& p, float duration) 
	        : player(p), stateDuration(duration) {}

void PlayerState::removeIfRegularState() {} //Do nothing for all except Regular (which overrides this)