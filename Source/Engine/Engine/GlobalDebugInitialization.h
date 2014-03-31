/////////////////////////
//GLOBAL VARIABLE LOADING
/////////////////////////
#pragma once
#include "DebugConsole.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

float DEBUG_CONSOLE;			//Shows debug side-car when on

float COLLISION_DEBUG;			//Shows bounding boxes when on
float STATE_DEBUG;				//Prints state info when on
float AUDIO_DEBUG;              //Prints audio info when on
float MENU_DEBUG;				//Prints menu info when on
float PLAYER_DRAG;				//Eliminates drag when off
float PLAYER_COLLIDE_OBSTACLE;	//No collision with obstacles when off
float PLAYER_NUMBER_OVERRIDE;   //Manually set number of players
float OBSTACLE_SPAWN;			//No obstacle spawning when off

float ENTITY_DRAG_SPEED;		//Speed that entities will automatically move towards end of playfield
float PLAYER_MOVEMENT_SPEED;	//Speed of player characters
float OBSTACLE_SPAWN_RATE;		//Multiplier for obstacle spawn rates

float GAME_PLAY_LENGTH;			//Length of game
float GAME_END_ANIMATION_LENGTH;//Length of "end game animation"

float PS_REGULAR_DURATION;		//Duration of PlayerRegularState
float PS_INJURED_DURATION;		//Duration of PlayerInjuredState
float PS_JUMP_DURATION;			//Duration of PlayerJumpState
float PS_JUMP_HEIGHT;			//Height of player characters' jumps
float PS_FLOAT_TO_VICTORY;		//Toggle for interesting end-of-game effect
float PS_ROLL_DURATION;			//Duration of PlayerRollState
float PS_BUMP_DURATION;			//Duration of PlayerBumpState
float PS_BUMP_HEIGHT;			//Height of player characters when bumped

float SPRITE_UPDATE_SPEED;		//Rate at which sprite animations update

float MENU_TITLE_X;				//X position of title
float MENU_TITLE_Y;				//Y position of title

#define TILDE 126
#define TILDECHAR '~'

float getNextFloat(ifstream& in)
{
	string readline;
	in.ignore(256, TILDE); 
	getline(in, readline, TILDECHAR);

	if (readline == "OFF")
		return 0.0f;
	else if (readline == "ON")
		return 1.0f;
	else
		return stof(readline);
}

void setAllGlobalVars()
{
	ifstream varValueFile("GlobalVariableValues.txt");
	if (varValueFile.is_open())
	{
		DEBUG_CONSOLE			= getNextFloat(varValueFile);

		COLLISION_DEBUG			= getNextFloat(varValueFile);
		STATE_DEBUG				= getNextFloat(varValueFile);
		AUDIO_DEBUG				= getNextFloat(varValueFile);
		MENU_DEBUG				= getNextFloat(varValueFile);
		PLAYER_DRAG				= getNextFloat(varValueFile);
		PLAYER_COLLIDE_OBSTACLE = getNextFloat(varValueFile);
		PLAYER_NUMBER_OVERRIDE  = getNextFloat(varValueFile);
		OBSTACLE_SPAWN			= getNextFloat(varValueFile);
		
		ENTITY_DRAG_SPEED		= getNextFloat(varValueFile);
		PLAYER_MOVEMENT_SPEED	= getNextFloat(varValueFile);
		OBSTACLE_SPAWN_RATE		= getNextFloat(varValueFile);

		GAME_PLAY_LENGTH			= getNextFloat(varValueFile);
		GAME_END_ANIMATION_LENGTH	= getNextFloat(varValueFile);

		PS_REGULAR_DURATION	= getNextFloat(varValueFile);
		PS_INJURED_DURATION = getNextFloat(varValueFile);
		PS_JUMP_DURATION	= getNextFloat(varValueFile);
		PS_JUMP_HEIGHT		= getNextFloat(varValueFile);
		PS_FLOAT_TO_VICTORY = getNextFloat(varValueFile);
		PS_ROLL_DURATION	= getNextFloat(varValueFile);
		PS_BUMP_DURATION	= getNextFloat(varValueFile);
		PS_BUMP_HEIGHT		= getNextFloat(varValueFile);

		SPRITE_UPDATE_SPEED	= getNextFloat(varValueFile);
		MENU_TITLE_X		= getNextFloat(varValueFile);
		MENU_TITLE_Y		= getNextFloat(varValueFile);
	}
}