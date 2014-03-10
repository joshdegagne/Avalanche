#include "PlayerJumpState.h"
#include "Player.h"

#include "DebugConsole.h"

PlayerJumpState::PlayerJumpState(Player& p, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_JUMP)
{
	writeLabelToConsole(L"Jump State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerJumpState::~PlayerJumpState()
{
	writeLabelToConsole(L"Jump State destroyed for Player ", player.getPlayerNum());
}

void PlayerJumpState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerJumpState::update(float elapsedTime)
{
	writeLabelToConsole(L"Jump State for Player 0 progress = ", timer.getProgressPercentage());
	timer.update(elapsedTime);
}

void PlayerJumpState::timerCallback()
{
	player.removeState(*this);
}
