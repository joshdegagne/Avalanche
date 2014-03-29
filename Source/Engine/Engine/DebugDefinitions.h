//Helper header for all debug statements. Comment out any you do not wish to use!
#pragma once

extern float COLLISION_DEBUG;			//Shows bounding boxes when on
extern float STATE_DEBUG;				//Prints state info when on
extern float AUDIO_DEBUG;               //Prints audio info when on
extern float PLAYER_DRAG;				//Eliminates drag when off
extern float PLAYER_COLLIDE_OBSTACLE;	//No collision with obstacles when off
extern float PLAYER_NUMBER_OVERRIDE;    //Manually set number of players
extern float OBSTACLE_SPAWN;			//No obstacle spawning when off

extern float ENTITY_DRAG_SPEED;			//Speed that entities will automatically move towards end of playfield
extern float PLAYER_MOVEMENT_SPEED;		//Speed of player characters
extern float OBSTACLE_SPAWN_RATE;		//Multiplier for obstacle spawn rates

extern float PS_REGULAR_DURATION;		//Duration of PlayerRegularState
extern float PS_INJURED_DURATION;		//Duration of PlayerInjuredState
extern float PS_JUMP_DURATION;			//Duration of PlayerJumpState
extern float PS_JUMP_HEIGHT;			//Height of player characters' jumps
extern float PS_FLOAT_TO_VICTORY;		//Toggle for interesting end-of-game effect
extern float PS_ROLL_DURATION;			//Duration of PlayerRollState
extern float PS_BUMP_DURATION;			//Duration of PlayerBumpState
extern float PS_BUMP_HEIGHT;			//Height of player characters when bumped

extern float SPRITE_UPDATE_SPEED;		//Rate at which sprite animations update

#define  STICK_MOVEMENT_THRESHOLD 0.3f
#define  TRIGGER_ACTIVATION_THRESHOLD 0.3f

#include "DebugConsole.h"



