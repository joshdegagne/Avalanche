#include "PlayerBumpState.h"
#include "Player.h"
#include "PlayerInjuredState.h"

#include "DebugDefinitions.h"

PlayerBumpState::PlayerBumpState(Player& p, bool isLeft, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_BUMPED), bumpedLeft(isLeft)
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Bump State created for Player ", player.getPlayerNum());
	#endif
	initialize();
}

PlayerBumpState::~PlayerBumpState()
{
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Bump State destroyed for Player ", player.getPlayerNum());
	#endif
}

void PlayerBumpState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerBumpState::update(float elapsedTime)
{
	updateBumpArc();
	if (bumpedLeft)
		player.moveLeft(elapsedTime, MOVEMENT_SPEED);
	else
		player.moveRight(elapsedTime, MOVEMENT_SPEED);
	timer.update(elapsedTime);
}

void PlayerBumpState::timerCallback(Timer& t)
{
	updateBumpArc();
	player.removeState(*this);
	if(!player.containsState(PlayerStateType::PST_INJURED))
		player.addState(*new PlayerInjuredState(player));
}

void PlayerBumpState::updateBumpArc()
{
	player.setHeight( getBumpArc(timer.getProgressPercentage()*100) );
	#ifdef STATE_DEBUG
	writeLabelToConsole(L"Bump Progress% for Player = ", timer.getProgressPercentage());
	writeLabelToConsole(L"Bump Height for Player = ", player.getPosition().z);
	#endif
}

float PlayerBumpState::getBumpArc(float timerProgress)
{
	float arc = ( ( -((timerProgress - 50.0f)/57.735f)*((timerProgress - 50.0f)/57.735f) ) + 0.75f);
	if (arc < 0)
		arc = 0;
	return arc;

}

bool PlayerBumpState::isBumpedLeft() { return bumpedLeft; }