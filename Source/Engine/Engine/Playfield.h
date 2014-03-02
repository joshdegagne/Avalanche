///////////////////////////////////////////////////////////////////////////////
// Filename: Playfield.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "arraylist.h"
#include "Player.h"
#include "QuadTexturedModel.h"
#include "QuadModel.h"
#include "Obstacle.h"
#include "Game.h"
#include "LogObstacle.h"
#include "RockObstacle.h"

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
		Playfield(); //Game pointer can come out of here when we no longer have test players
		~Playfield();

		void initialize(Game*);
		void update(float); // for scrolling

		ArrayList<GameModel>*	getGameModels(); 
		ArrayList<IViewModel>*  getViewModels();

	private:
		ArrayList<Entity>*		entities;			//List of entities CURRENTLY BEING UPDATED
		ArrayList<Player>*		activePlayers;		//List of players in the current match
		ArrayList<Obstacle>*	obstacles;			//List of obstacles (Finite bag/number of obstacles)
		ArrayList<GameModel>*   models;				//list of models to pass to game
		ArrayList<IViewModel>*  viewModels;			//List of IViewModels (So far just Player and LogObstacle)
		QuadTexturedModel*		ground;				//Playfield quad
		QuadModel*				deathArea;			//Death quad

		const float fieldLength;
		const float fieldWidth;

		void populateLists(Game* game);

		void addObstacleToPlayfield(Obstacle*, int lane = -1);
		void kill(Entity*);
		void placeObstacle(Obstacle*, int lane = -1);

		void checkPlayerBounds(Player*);
};