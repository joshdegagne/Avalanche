///////////////////////////////////////////////////////////////////////////////
// Filename: Playfield.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "arraylist.h"
#include "Player.h"
#include "QuadTexturedModel.h"
#include "Obstacle.h"
#include "ControllerInputManager.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: Playfield
// The main encapsulation of the entities and management of said entities
////////////////////////////////////////////////////////////////////////////////
class Playfield
{
	public:
		Playfield();
		~Playfield();
		void Initialize(int numPlayers, ControllerInputManager*);
	private:
		ArrayList<Obstacle>*	obstacles;	  //List of obstacles
		Player*					players [4];  //List of players
		ControllerInputManager* input;		  //Input Manager
		QuadTexturedModel*		ground;	      //Playfield quad
};