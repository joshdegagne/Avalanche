#include "PlayerRegularState.h"
#include "Timer-inl.h"
#include "Player.h"

PlayerRegularState::PlayerRegularState(Player& p, float duration) : PlayerState(p, duration)
{
	timer = new Timer<PlayerRegularState>;
	initialize();
}

PlayerRegularState::~PlayerRegularState()
{
	
}

void PlayerRegularState::initialize()
{
	timer->initialize(0.0f, &PlayerRegularState::stateEnd);
}

void PlayerRegularState::update(float elapsedTime)
{
	timer->update(elapsedTime);
}

void PlayerRegularState::stateEnd()
{
	
}

void PlayerRegularState::removeIfRegularState()
{
	player.removeState(*this);
}
