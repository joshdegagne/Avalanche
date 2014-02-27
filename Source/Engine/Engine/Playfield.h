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
		Playfield(Game*); //Game pointer can come out of here when we no longer have test players
		~Playfield();

		// initialize method?
		void update(float); // for scrolling

		ArrayList<GameModel>*	getGameModels(); 
		ArrayList<IViewModel>*  getViewModels();

	protected:
		void add(Player* player);

	private:
		ArrayList<Entity>*		entities;
		ArrayList<Player>*		activePlayers;			//List of players in the current match
		ArrayList<Obstacle>*	obstacles;			//List of obstacles
		ArrayList<GameModel>*   models;				//list of models to pass to game
		ArrayList<IViewModel>*  viewModels;
		QuadTexturedModel*		ground;				//Playfield quad
		LogModel*				testLogModel;		//made to test scrolling

		const float fieldLength;
		const float fieldWidth;

		void placeObstacle(Obstacle*, int lane = -1);
};