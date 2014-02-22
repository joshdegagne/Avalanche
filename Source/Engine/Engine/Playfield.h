///////////////////////////////////////////////////////////////////////////////
// Filename: Playfield.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "arraylist.h"
#include "Player.h"
#include "QuadTexturedModel.h"
#include "Obstacle.h"
#include "Game.h"
#include "LogObstacle.h"
#include "LogModel.h"

#define SCROLL_SPEED 0.15f

class Player; //Foward declaration needed in order to satisfy compiler
////////////////////////////////////////////////////////////////////////////////
// Class name: Playfield
// The main encapsulation of the entities and management of said entities
////////////////////////////////////////////////////////////////////////////////
class Playfield
{
	public:
		Playfield(Player**, int);
		~Playfield();

		// initialize method?
		void update(float); // for scrolling

		LogModel* getTestLogModel(); // made to test scrolling
	private:
		ArrayList<Obstacle>*	obstacles;		   //List of obstacles
		Player**				activePlayers;	   //List of players (will be of length 1-4)
		int						numActivePlayers;  //Number of players
		ControllerInputManager* input;			   //Input Manager
		QuadTexturedModel*		ground;	           //Playfield quad
		LogModel*				testLogModel;	   //made to test scrolling
};