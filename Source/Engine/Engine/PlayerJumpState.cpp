#include "PlayerJumpState.h"

PlayerJumpState::PlayerJumpState(Player& p, float duration = -1.0f) : PlayerState(p, duration)
{
	timer = new Timer<PlayerJumpState>;
	initialize();
}

PlayerJumpState::~PlayerJumpState()
{
	
}

void PlayerJumpState::initialize()
{
	
}

void PlayerJumpState::update()
{
	
}

void PlayerJumpState::stateEnd()
{
	
}
