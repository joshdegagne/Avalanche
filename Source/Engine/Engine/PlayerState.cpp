#include "PlayerState.h"

PlayerState::PlayerState(Player& p, float duration, PlayerStateType pst) 
	        : player(p), stateDuration(duration), PST(pst) {}

PlayerState::~PlayerState() {}

PlayerStateType PlayerState::getStateType() { return PST; }

float PlayerState::getProgressPercentage() { return timer.getProgressPercentage(); }