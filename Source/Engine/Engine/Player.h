///////////////////////////////////////////////////////////////////////////////
// Filename: Player.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity.h"
#include "Game.h"
#include "BoundingBox.h"
#include "Obstacle.h"
#include "IPlayerListener.h"
#include "PlayerState.h"

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
		int			getPlayerNum();
		void		update(float);
		void		render(); 

		void onCollide(Player&);	//NEW
		void onCollide(Obstacle&);	//NEW
		
		void addListener(IPlayerListener&);
		void removeListener(IPlayerListener&);
		void addState(PlayerState&);			//NEW
		void removeState(PlayerState&);			//NEW
		
		void lockLeftMovement(bool = true);
		void lockRightMovement(bool = true);
		void lockForwardMovement(bool = true);

	private:
		KeyInput*	 keyboard;
		int			 keys[5];
		ControllerInputManager*		controller;
		ArrayList<PlayerState>		states;		//NEW
		ArrayList<IPlayerListener>	listeners;	//NEW

		int			playerNum; //This was created for use with the ControllerInputManager. Valid nums are [0-3]
		XMFLOAT2	velocity;
		bool		movementLocks[3]; //Used for bounds checking in the playfield
		float       jumpIncrement;

		void checkControllerInputs(float);
		void checkKeyboardInputs(float);
		void notifyStateStart(PlayerState&); //NEW
		void notifyStateEnd(PlayerState&);	 //NEW

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