#include "PlayerBumpState.h"
#include "Player.h"
#include "PlayerInjuredState.h"

#include "DebugDefinitions.h"

PlayerBumpState::PlayerBumpState(Player& p, bool isLeft, float duration) 
				: PlayerState(p, duration, PlayerStateType::PST_BUMPED), bumpedLeft(isLeft)
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Bump State created for Player ", player.getPlayerNum());
	initialize();
}

PlayerBumpState::~PlayerBumpState()
{
	if(STATE_DEBUG)
		writeLabelToConsole(L"Bump State destroyed for Player ", player.getPlayerNum());
}

void PlayerBumpState::initialize()
{
	timer.initialize(stateDuration, this);
}

void PlayerBumpState::update(float elapsedTime)
{
	updateBumpArc();
	if (bumpedLeft)
		player.moveLeft(elapsedTime, PLAYER_MOVEMENT_SPEED);
	else
		player.moveRight(elapsedTime, PLAYER_MOVEMENT_SPEED);
	timer.update(elapsedTime);
}

void PlayerBumpState::timerCallback(Timer& t)
{
	updateBumpArc();
	if(!player.containsState(PlayerStateType::PST_INJURED))
		player.addState(*new PlayerInjuredState(player));
	player.removeState(*this);
}

void PlayerBumpState::updateBumpArc()
{
	player.setHeight( getBumpArc(timer.getProgressPercentage()*100) );
}

float PlayerBumpState::getBumpArc(float timerProgress)
{
	float arc = ( ( -((timerProgress - 50.0f)/50.0f)*((timerProgress - 50.0f)/50.0f) ) + 1) * PS_BUMP_HEIGHT;
	if (arc < 0)
		arc = 0;
	return arc;

}

bool PlayerBumpState::isBumpedLeft() { return bumpedLeft; }