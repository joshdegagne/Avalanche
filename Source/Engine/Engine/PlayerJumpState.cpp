#include "PlayerJumpState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerJumpState::PlayerJumpState(Player& p, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_JUMP)
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Jump State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerJumpState::~PlayerJumpState()
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Jump State destroyed for Player ", player.getPlayerNum());
}

void PlayerJumpState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerJumpState::update(float elapsedTime)
{
	updateJumpArc();
	timer.update(elapsedTime);
}

void PlayerJumpState::timerCallback(Timer& t)
{
	updateJumpArc();
	player.removeState(*this);
}

void PlayerJumpState::updateJumpArc()
{
	player.setHeight( getJumpArc(timer.getProgressPercentage()*100) );
}

float PlayerJumpState::getJumpArc(float timerProgress)
{
	float arc = ( ( -((timerProgress - 50.0f)/50.0f)*((timerProgress - 50.0f)/50.0f) ) + 1) * PS_JUMP_HEIGHT;
	if (arc < 0)
		arc = 0;
	return arc;

}
