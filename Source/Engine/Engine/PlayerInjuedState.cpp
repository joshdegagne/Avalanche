#include "PlayerInjuredState.h"

PlayerInjuredState::PlayerInjuredState(Player& p, float duration = -1.0f) : PlayerState(p, duration)
{
	timer = new Timer<PlayerInjuredState>;
	initialize();
}

PlayerInjuredState::~PlayerInjuredState()
{
	
}

void PlayerInjuredState::initialize()
{
	
}

void PlayerInjuredState::update()
{
	
}

void PlayerInjuredState::stateEnd()
{
	
}
