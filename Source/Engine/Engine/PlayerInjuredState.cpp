#include "PlayerInjuredState.h"
#include "Timer-inl.h"

PlayerInjuredState::PlayerInjuredState(Player& p, float duration) : PlayerState(p, duration)
{
	timer = new Timer<PlayerInjuredState>;
	initialize();
}

PlayerInjuredState::~PlayerInjuredState()
{
	
}

void PlayerInjuredState::initialize()
{
	timer->initialize(0.0f, &PlayerInjuredState::stateEnd);
}

void PlayerInjuredState::update(float elapsedTime)
{
	timer->update(elapsedTime);
}

void PlayerInjuredState::stateEnd()
{
	
}
