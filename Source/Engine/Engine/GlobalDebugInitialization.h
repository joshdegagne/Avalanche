/////////////////////////
//GLOBAL VARIABLE LOADING
/////////////////////////
#pragma once
#include "DebugConsole.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

float COLLISION_DEBUG;			//Shows bounding boxes when on
float STATE_DEBUG;				//Prints state info when on
float AUDIO_DEBUG;              //Prints audio info when on
float PLAYER_DRAG;				//Eliminates drag when off
float PLAYER_COLLIDE_OBSTACLE;	//No collision with obstacles when off
float OBSTACLE_SPAWN;			//No obstacle spawning when off

float ENTITY_DRAG_SPEED;
float PLAYER_MOVEMENT_SPEED;
float OBSTACLE_SPAWN_RATE;

float PS_REGULAR_DURATION;
float PS_INJURED_DURATION;
float PS_JUMP_DURATION;
float PS_JUMP_HEIGHT;
float PS_FLOAT_TO_VICTORY;
float PS_ROLL_DURATION;
float PS_BUMP_DURATION;
float PS_BUMP_HEIGHT;

float SPRITE_UPDATE_SPEED;

#define TILDE 126
#define TILDECHAR '~'

float getNextFloat(ifstream& in)
{
	string readline;
	in.ignore(256, TILDE); 
	getline(in, readline, TILDECHAR);
	if (readline == "OFF")
	{
		writeStringToConsole(readline);
		return 0.0f;
	}
	else if (readline == "ON")
	{
		writeStringToConsole(readline);
		return 1.0f;
	}
	else
	{
		writeNumToConsole(stof(readline));
		return stof(readline);
	}
}

void setAllGlobalVars()
{
	ifstream varValueFile("GlobalVariableValues.txt");
	if (varValueFile.is_open())
	{
		COLLISION_DEBUG			= getNextFloat(varValueFile);
		STATE_DEBUG				= getNextFloat(varValueFile);
		AUDIO_DEBUG				= getNextFloat(varValueFile);
		PLAYER_DRAG				= getNextFloat(varValueFile);
		PLAYER_COLLIDE_OBSTACLE = getNextFloat(varValueFile);
		OBSTACLE_SPAWN			= getNextFloat(varValueFile);
		
		ENTITY_DRAG_SPEED		= getNextFloat(varValueFile);
		PLAYER_MOVEMENT_SPEED	= getNextFloat(varValueFile);
		OBSTACLE_SPAWN_RATE		= getNextFloat(varValueFile);

		PS_REGULAR_DURATION	= getNextFloat(varValueFile);
		PS_INJURED_DURATION = getNextFloat(varValueFile);
		PS_JUMP_DURATION	= getNextFloat(varValueFile);
		PS_JUMP_HEIGHT		= getNextFloat(varValueFile);
		PS_FLOAT_TO_VICTORY = getNextFloat(varValueFile);
		PS_ROLL_DURATION	= getNextFloat(varValueFile);
		PS_BUMP_DURATION	= getNextFloat(varValueFile);
		PS_BUMP_HEIGHT		= getNextFloat(varValueFile);

		SPRITE_UPDATE_SPEED	= getNextFloat(varValueFile);
	}
}