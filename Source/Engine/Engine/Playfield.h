///////////////////////////////////////////////////////////////////////////////
// Filename: Playfield.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "arraylist.h"
#include "Player.h"
#include "QuadTexturedModel.h"
#include "QuadModel.h"
#include "Obstacle.h"
#include "ObstacleBag.h"
#include "Game.h"
#include "LogObstacle.h"
#include "RockObstacle.h"
#include "CollisionManager.h"

#define SCROLL_SPEED 0.15f
#define NUM_LANES 6
#define GAME_LENGTH 300000.0f //5 Minutes

class Player; //Foward declaration needed in order to satisfy compiler
class Game;
////////////////////////////////////////////////////////////////////////////////
// Class name: Playfield
// The main encapsulation of the entities and management of said entities
////////////////////////////////////////////////////////////////////////////////
class Playfield : public ITimedObject
{
	public:
		Playfield(); //Game pointer can come out of here when we no longer have test players
		~Playfield();

		void initialize(Game*);
		void update(float); // for scrolling

		ArrayList<GameModel>*	getGameModels(); 

		void timerCallback();

	private:
		ArrayList<Entity>*		entities;			//List of entities CURRENTLY BEING UPDATED
		ArrayList<Player>*		activePlayers;		//List of players in the current match
		//ArrayList<Obstacle>*	obstacles;			//List of obstacles (Finite bag/number of obstacles)
		ObstacleBag*			obstacleBag;
		ArrayList<GameModel>*   models;				//list of models to pass to game
		QuadTexturedModel*		ground;				//Playfield quad
		QuadModel*				deathArea;			//Death quad

		CollisionManager*		collisionManager;

		Timer timer;
		float previousProgressPercentage;
		float percentageBetweenObstacles;

		const float fieldLength;
		const float fieldWidth;

		void populateLists(Game* game);

		int getLaneAlgorithm(Obstacle*);
		void addObstacleToPlayfield();
		//void addObstacleToPlayfield(Obstacle*, int lane = -1);
		void kill(Entity*);
		void placeObstacle(Obstacle*, int lane = -1);

		void checkPlayerBounds(Player*);
};