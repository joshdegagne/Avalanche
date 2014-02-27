///////////////////////////////////////////////////////////////////////////////
// Filename: Player.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity.h"
#include "Game.h"
#include "Cubemodel.h" // for testing movement via controller
#include "QuadModel.h" // for testing movement via controller
#include "PlayerModel.h" // for testing
#include "BoundingBox.h"

#define  STICK_MOVEMENT_THRESHOLD 0.3f
#define  TRIGGER_ACTIVATION_THRESHOLD 0.3f
#define	 MOVEMENT_SPEED 0.006f
#define  JUMP_HEIGHT 4.0f

#define  P_WIDTH  1.0f
#define  P_LENGTH 1.0f
#define  P_HEIGHT 1.0f

class Game;  //Forward declaration
////////////////////////////////////////////////////////////////////////////////
// Class name: Player
////////////////////////////////////////////////////////////////////////////////
class Player: public Entity {
	public: 
		//Constructors
		Player(Game&, int);
		~Player();
		GameModel*	getPlayerModel(); 
		void		update(float);
		void		render(); 

	private:
		GameModel*	 playerModel; // for testing purposes
		ControllerInputManager* controller;
		KeyInput*	 keyboard;
		int			 keys[4];

		int			playerNum; //This was created for use with the ControllerInputManager. Valid nums are [0-3]
		XMFLOAT2	velocity;
		float       jumpIncrement;

		void checkControllerInputs();
		void checkKeyboardInputs();

		//Movement
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void stop();
	
	public: //TEMPORARILY PUBLIC FOR KEYBOARD TESTING
		//Possible jump implementation (no real physics simulation here)
		void jump(float);
		void jumpArc(float);
		//rollLeft();
		//rollRight();
		//requestPause(); ???

};