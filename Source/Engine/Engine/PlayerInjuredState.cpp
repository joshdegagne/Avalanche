#include "PlayerInjuredState.h"
#include "Player.h"

#include "DebugConsole.h"

PlayerInjuredState::PlayerInjuredState(Player& p, float duration)
				   : PlayerState(p, duration, PlayerStateType::PST_INJURED)
{
	writeLabelToConsole(L"Injured State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerInjuredState::~PlayerInjuredState()
{
	writeLabelToConsole(L"Injured State destroyed for Player ", player.getPlayerNum());
}

void PlayerInjuredState::initialize()
{
	writeLabelToConsole(L"State Duration: ", stateDuration);
	timer.initialize(stateDuration, this);
}

void PlayerInjuredState::update(float elapsedTime)
{
	writeLabelToConsole(L"Injured State for Player progress = ", timer.getProgressPercentage());
	timer.update(elapsedTime);
}

void PlayerInjuredState::timerCallback()
{
	player.removeState(*this);
}
