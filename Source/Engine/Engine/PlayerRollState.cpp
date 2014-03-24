#include "PlayerRollState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerRollState::PlayerRollState(Player& p, bool isLeft, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_ROLL), rollingLeft(isLeft)
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Roll State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerRollState::~PlayerRollState()
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Roll State destroyed for Player ", player.getPlayerNum());
}

void PlayerRollState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerRollState::update(float elapsedTime)
{
	if (rollingLeft)
		player.moveLeft(elapsedTime, PLAYER_MOVEMENT_SPEED*1.75f);
	else
		player.moveRight(elapsedTime, PLAYER_MOVEMENT_SPEED*1.75f);
	timer.update(elapsedTime);
}

void PlayerRollState::timerCallback(Timer& t)
{
	player.removeState(*this);
}

bool PlayerRollState::isRollingLeft() { return rollingLeft; }
