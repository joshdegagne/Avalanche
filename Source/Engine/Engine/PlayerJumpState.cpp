#include "PlayerJumpState.h"
#include "Timer-inl.h"

PlayerJumpState::PlayerJumpState(Player& p, float duration) : PlayerState(p, duration)
{
	timer = new Timer<PlayerJumpState>;
	initialize();
}

PlayerJumpState::~PlayerJumpState()
{
	
}

void PlayerJumpState::initialize()
{
	timer->initialize(0.0f, &PlayerJumpState::stateEnd);
}

void PlayerJumpState::update(float elapsedTime)
{
	timer->update(elapsedTime);
}

void PlayerJumpState::stateEnd()
{
	
}
