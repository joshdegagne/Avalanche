///////////////////////////////////////////////////////////////////////////////
// Filename: Player.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity.h"
#include "Game.h"
#include "Cubemodel.h"

#define  STICK_MOVEMENT_THRESHOLD 0.3f
#define  TRIGGER_ACTIVATION_THRESHOLD 0.3f
#define	 MOVEMENT_SPEED 0.1f

class Game;  //Forward declaration
////////////////////////////////////////////////////////////////////////////////
// Class name: Player
////////////////////////////////////////////////////////////////////////////////
class Player: public Entity {
	public: 
		//Constructors
		Player(Game&, int);
		
		void update(float);
		CubeModel* getModel();
		void render(); 

	private:
		ControllerInputManager* controller;
		int			playerNum; //This was created for use with the ControllerInputManager. Valid nums are [0-3]
		XMFLOAT2	position;
		CubeModel*	model;
	
	public: //TEMPORARILY PUBLIC FOR KEYBOARD TESTING
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		//jump();
		//rollLeft();
		//rollRight();
		//requestPause(); ???

};