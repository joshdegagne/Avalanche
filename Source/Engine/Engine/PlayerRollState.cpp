#include "PlayerRollState.h"
#include "Player.h"

#include "DebugConsole.h"

PlayerRollState::PlayerRollState(Player& p, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_ROLL)
{
	writeLabelToConsole(L"Roll State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerRollState::~PlayerRollState()
{
	writeLabelToConsole(L"Roll State destroyed for Player ", player.getPlayerNum());
}

void PlayerRollState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerRollState::update(float elapsedTime)
{
	writeLabelToConsole(L"Roll State for Player 0 progress = ", timer.getProgressPercentage());
	timer.update(elapsedTime);
}

void PlayerRollState::timerCallback()
{
	player.removeState(*this);
}
