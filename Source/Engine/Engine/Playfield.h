///////////////////////////////////////////////////////////////////////////////
// Filename: Playfield.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "arraylist.h"
#include "Player.h"
#include "QuadTexturedModel.h"
#include "Obstacle.h"
#include "Game.h"

class Game; //Foward declaration needed in order to satisfy compiler
////////////////////////////////////////////////////////////////////////////////
// Class name: Playfield
// The main encapsulation of the entities and management of said entities
////////////////////////////////////////////////////////////////////////////////
class Playfield
{
	public:
		Playfield(Player**, int);
		~Playfield();
	private:
		ArrayList<Obstacle>*	obstacles;		   //List of obstacles
		Player**				activePlayers;	   //List of players
		int						numActivePlayers;  //Number of players
		ControllerInputManager* input;			   //Input Manager
		QuadTexturedModel*		ground;	           //Playfield quad
};