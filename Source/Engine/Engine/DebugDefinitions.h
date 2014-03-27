//Helper header for all debug statements. Comment out any you do not wish to use!
#pragma once

extern float COLLISION_DEBUG;			//Shows bounding boxes when on
extern float STATE_DEBUG;				//Prints state info when on
extern float AUDIO_DEBUG;               //Prints audio info when on
extern float PLAYER_DRAG;				//Eliminates drag when off
extern float PLAYER_COLLIDE_OBSTACLE;	//No collision with obstacles when off
extern float OBSTACLE_SPAWN;			//No obstacle spawning when off

extern float ENTITY_DRAG_SPEED;			//Drag Speed
extern float PLAYER_MOVEMENT_SPEED;		//Player Movement Speed
extern float OBSTACLE_SPAWN_RATE;		//Multiplier for Obstacle Spawning

extern float PS_REGULAR_DURATION;
extern float PS_INJURED_DURATION;
extern float PS_JUMP_DURATION;
extern float PS_JUMP_HEIGHT;
extern float PS_ROLL_DURATION;
extern float PS_BUMP_DURATION;
extern float PS_BUMP_HEIGHT;

extern float SPRITE_UPDATE_SPEED;

#define  STICK_MOVEMENT_THRESHOLD 0.3f
#define  TRIGGER_ACTIVATION_THRESHOLD 0.3f

#include "DebugConsole.h"



