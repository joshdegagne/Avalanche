#include "PlayerRollState.h"
#include "Player.h"

#include "DebugConsole.h"

PlayerRollState::PlayerRollState(Player& p, bool isLeft, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_ROLL), rollingLeft(isLeft)
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
	if (rollingLeft)
		player.moveLeft(elapsedTime, MOVEMENT_SPEED*1.5f);
	else
		player.moveRight(elapsedTime, MOVEMENT_SPEED*1.5f);
	timer.update(elapsedTime);
}

void PlayerRollState::timerCallback()
{
	player.removeState(*this);
}

bool PlayerRollState::isRollingLeft() { return rollingLeft; }
