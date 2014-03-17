#include "PlayerJumpState.h"
#include "Player.h"

#include "DebugDefinitions.h"

PlayerJumpState::PlayerJumpState(Player& p, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_JUMP)
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Jump State created for Player ", player.getPlayerNum());
	#endif
	initialize();
}

PlayerJumpState::~PlayerJumpState()
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Jump State destroyed for Player ", player.getPlayerNum());
	#endif
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

void PlayerJumpState::timerCallback()
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
	float arc = ( ( -((timerProgress - 50.0f)/35.3535f)*((timerProgress - 50.0f)/35.3535f) ) +2);
	if (arc < 0)
		arc = 0;
	return arc;

}
