#include "PlayerInjuredState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerInjuredState::PlayerInjuredState(Player& p, float duration)
				   : PlayerState(p, duration, PlayerStateType::PST_INJURED)
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Injured State created for Player ", player.getPlayerNum());
	#endif
	initialize();
	
}

PlayerInjuredState::~PlayerInjuredState()
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Injured State destroyed for Player ", player.getPlayerNum());
	#endif
}

void PlayerInjuredState::initialize()
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"State Duration: ", stateDuration);
	#endif
	timer.initialize(stateDuration, this);
}

void PlayerInjuredState::update(float elapsedTime)
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Injured State for Player progress = ", timer.getProgressPercentage());
	#endif
	timer.update(elapsedTime);
}

void PlayerInjuredState::timerCallback()
{
	player.removeState(*this);
}
