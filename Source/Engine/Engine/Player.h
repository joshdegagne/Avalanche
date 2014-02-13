///////////////////////////////////////////////////////////////////////////////
// Filename: Player.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity.h"
#include "Game.h"
#include "Cubemodel.h"

#define  STICK_MOVEMENT_THRESHOLD 0.3
#define  TRIGGER_ACTIVATION_THRESHOLD 0.3

class Game;  //Forward declaration
////////////////////////////////////////////////////////////////////////////////
// Class name: Player
////////////////////////////////////////////////////////////////////////////////
class Player: public Entity {
	public: 
		//Constructors
		Player(Game&, int);
		
		void update(float);

	private:
		ControllerInputManager* controller;
		int			playerNum; //This was created for use with the ControllerInputManager. Valid nums are [0-3]
		XMFLOAT2	position;
		CubeModel*	model;
		
		void render(); 
		//moveLeft();
		//moveRight();
		//moveUp();
		//moveDown();
		//jump();
		//rollLeft();
		//rollRight();
		//requestPause(); ???

};