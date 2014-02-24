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
class Game;
////////////////////////////////////////////////////////////////////////////////
// Class name: Playfield
// The main encapsulation of the entities and management of said entities
////////////////////////////////////////////////////////////////////////////////
class Playfield
{
	public:
		Playfield(Player**, int, Game*); //Game pointer can come out of here when we no longer have test players
		~Playfield();

		// initialize method?
		void update(float); // for scrolling

		ArrayList<GameModel>* getGameModels(); 

	private:
		ArrayList<Obstacle>*	obstacles;			//List of obstacles
		ArrayList<GameModel>*   models;				//list of models to pass to game
		Player**				activePlayers;		//List of players (will be of length 1-4)
		Player**                testPlayers;		//List of players for testing w/o controllers
		int						numActivePlayers;	//Number of players
		QuadTexturedModel*		ground;				//Playfield quad
		LogModel*				testLogModel;		//made to test scrolling
};