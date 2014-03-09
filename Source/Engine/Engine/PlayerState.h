////////////////////////////////////////////////////////////////////////////////
// Filename: PlayerState.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "arraylist.h"
#include "Timer.h"

#define PS_REGULAR_DURATION -1.0f
#define PS_INJURED_DURATION -1.0f
#define PS_JUMP_DURATION -1.0f
#define PS_ROLL_DURATION -1.0f

// Forward Declarations
class Player;
class Obstacle;

////////////////////////////////////////////////////////////////////////////////
// Abstract class name: PlayerState
////////////////////////////////////////////////////////////////////////////////
class PlayerState {
public:
	PlayerState(Player&, float);

//	virtual void onCollideWith(Player*)   = 0;
//	virtual void onCollideWith(Obstacle*) = 0;
	virtual void initialize()  = 0;
	virtual void update(float) = 0;
	virtual void stateEnd()    = 0;
	virtual void removeIfRegularState();

protected:
	Player& player;
	float   stateDuration;
};