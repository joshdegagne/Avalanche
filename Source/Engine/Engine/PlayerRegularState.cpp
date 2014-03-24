#include "PlayerRegularState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerRegularState::PlayerRegularState(Player& p, float duration) 
				   : PlayerState(p, duration, PlayerStateType::PST_REGULAR)
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Regular State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerRegularState::~PlayerRegularState()
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Regular State destroyed for Player ", player.getPlayerNum());
}

void PlayerRegularState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerRegularState::update(float elapsedTime)
{
	timer.update(elapsedTime);
}

void PlayerRegularState::timerCallback(Timer& t)
{
	player.removeState(*this);
}
