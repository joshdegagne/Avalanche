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
#define	 MOVEMENT_SPEED 0.004f
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
		void addState(PlayerState&);				//NEW
		void removeState(PlayerState&);				//NEW
		bool containsState(PlayerStateType PST);		//NEW
		
		void lockLeftMovement(bool = true);
		void lockRightMovement(bool = true);
		void lockForwardMovement(bool = true);
		
	private:
		KeyInput*	 keyboard;
		int			 keys[7];
		ControllerInputManager*		controller;
		ArrayList<PlayerState>		states;		//NEW
		ArrayList<IPlayerListener>	listeners;	//NEW

		int			playerNum; //This was created for use with the ControllerInputManager. Valid nums are [0-3]
		XMFLOAT2	velocity;
		float		speed;
		bool		movementLocks[3]; //Used for bounds checking in the playfield
		float       jumpIncrement;

		void checkControllerInputs(float);
		void checkKeyboardInputs(float);
		void notifyStateStart(PlayerState&); //NEW
		void notifyStateEnd(PlayerState&);	 //NEW

		
	
	public: //TEMPORARILY PUBLIC FOR KEYBOARD TESTING

		//Movement
		void moveLeft(float elapsed, float speed = MOVEMENT_SPEED);
		void moveRight(float elapsed, float speed = MOVEMENT_SPEED);
		void moveUp(float elapsed, float speed = MOVEMENT_SPEED);
		void moveDown(float elapsed, float speed = MOVEMENT_SPEED);
		void stop();
	
		//Possible jump implementation (no real physics simulation here)
		void setHeight(float);
		void jump();
		void jumpArc(float);
		void rollLeft();
		void rollRight();
		//requestPause(); ???

};