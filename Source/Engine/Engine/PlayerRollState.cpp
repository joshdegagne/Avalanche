#include "PlayerRollState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerRollState::PlayerRollState(Player& p, bool isLeft, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_ROLL), rollingLeft(isLeft)
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Roll State created for Player ", player.getPlayerNum());
	#endif
	initialize();
}

PlayerRollState::~PlayerRollState()
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Roll State destroyed for Player ", player.getPlayerNum());
	#endif
}

void PlayerRollState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerRollState::update(float elapsedTime)
{
	if (rollingLeft)
		player.moveLeft(elapsedTime, MOVEMENT_SPEED*1.75f);
	else
		player.moveRight(elapsedTime, MOVEMENT_SPEED*1.75f);
	timer.update(elapsedTime);
}

void PlayerRollState::timerCallback()
{
	player.removeState(*this);
}

bool PlayerRollState::isRollingLeft() { return rollingLeft; }
