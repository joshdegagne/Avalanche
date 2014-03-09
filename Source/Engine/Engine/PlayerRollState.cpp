#include "PlayerRollState.h"
#include "Timer-inl.h"

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
	timer->initialize(0.0f, &PlayerRollState::stateEnd);
}

void PlayerRollState::update(float elapsedTime)
{
	timer->update(elapsedTime);
}

void PlayerRollState::stateEnd()
{
	
}
