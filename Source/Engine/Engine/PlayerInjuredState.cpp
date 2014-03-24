#include "PlayerInjuredState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerInjuredState::PlayerInjuredState(Player& p, float duration)
				   : PlayerState(p, duration, PlayerStateType::PST_INJURED)
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Injured State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerInjuredState::~PlayerInjuredState()
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Injured State destroyed for Player ", player.getPlayerNum());
}

void PlayerInjuredState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerInjuredState::update(float elapsedTime)
{
	if (timer.getProgressPercentage() < 0.33f)
		player.moveUp(elapsedTime, ENTITY_DRAG_SPEED*1.25f);
	timer.update(elapsedTime);
}

void PlayerInjuredState::timerCallback(Timer& t)
{
	player.removeState(*this);
}
