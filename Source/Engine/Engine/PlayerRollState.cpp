#include "PlayerRollState.h"

PlayerRollState::PlayerRollState(Player& p, float duration = -1.0f) : PlayerState(p, duration)
{
	timer = new Timer<PlayerRollState>;
	initialize();
}

PlayerRollState::~PlayerRollState()
{
	
}

void PlayerRollState::initialize()
{
	
}

void PlayerRollState::update()
{
	
}

void PlayerRollState::stateEnd()
{
	
}
