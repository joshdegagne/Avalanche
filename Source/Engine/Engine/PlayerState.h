////////////////////////////////////////////////////////////////////////////////
// Filename: PlayerState.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "arraylist.h"
#include "Timer.h"
#include "ITimedObject.h"

#define PS_REGULAR_DURATION -1.0f
#define PS_INJURED_DURATION 500.0f
#define PS_JUMP_DURATION 600.0f
#define PS_ROLL_DURATION 300.0f
#define PS_BUMP_DURATION 200.0f

enum class PlayerStateType : int 
{
	PST_DEFAULT = 0, 
	PST_REGULAR, 
	PST_INJURED,
	PST_JUMP,
	PST_ROLL,
	PST_BUMPED
};

// Forward Declarations
class Player;
class Obstacle;

////////////////////////////////////////////////////////////////////////////////
// Abstract class name: PlayerState
////////////////////////////////////////////////////////////////////////////////
class PlayerState : public ITimedObject {
public:
	PlayerState(Player&, float, PlayerStateType = PlayerStateType::PST_DEFAULT);
	virtual ~PlayerState();

//	virtual void onCollideWith(Player*)   = 0;
//	virtual void onCollideWith(Obstacle*) = 0;
	virtual void initialize()  = 0;
	virtual void update(float) = 0;

	PlayerStateType getStateType();

protected:
	Player&			player;
	PlayerStateType PST;
	Timer			timer;
	float			stateDuration;
};