#include "PlayerRegularState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerRegularState::PlayerRegularState(Player& p, float duration) 
				   : PlayerState(p, duration, PlayerStateType::PST_REGULAR)
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Regular State created for Player ", player.getPlayerNum());
	#endif
	initialize();
}

PlayerRegularState::~PlayerRegularState()
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Regular State destroyed for Player ", player.getPlayerNum());
	#endif
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
