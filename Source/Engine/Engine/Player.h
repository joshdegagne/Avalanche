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
#include "DebugDefinitions.h"


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

		void initialize();
		void update(float);
		
		int	 getPlayerNum();
		bool requestingPause();

		void onCollide(Player&, float);
		void onCollide(Obstacle&);

		void addListener(IPlayerListener&);
		void removeListener(IPlayerListener&);
		void addState(PlayerState&);
		void removeState(PlayerState&);
		bool containsState(PlayerStateType PST);
		
		void lockLeftMovement(bool = true);
		void lockRightMovement(bool = true);
		void lockForwardMovement(bool = true);
		
	private:
		KeyInput*	 keyboard;
		int			 keys[7];
		ControllerInputManager*		controller;
		ArrayList<PlayerState>		states;		//NEW
		ArrayList<IPlayerListener>	listeners;	//NEW

		//Flags for input
		bool A_FLAG, B_FLAG, X_FLAG, Y_FLAG, LB_FLAG, RB_FLAG, LT_FLAG, RT_FLAG, START_FLAG;

		int			playerNum; //This was created for use with the ControllerInputManager. Valid nums are [0-3]
		XMFLOAT2	velocity;
		bool		movementLocks[3]; //Used for bounds checking in the playfield

		void checkControllerInputs(float);
		void checkKeyboardInputs(float);
		void notifyStateStart(PlayerState&); //NEW
		void notifyStateEnd(PlayerState&);	 //NEW

		
	
	public: //TEMPORARILY PUBLIC FOR KEYBOARD TESTING

		//Movement
		void moveLeft(float elapsed, float speed = PLAYER_MOVEMENT_SPEED);
		void moveRight(float elapsed, float speed = PLAYER_MOVEMENT_SPEED);
		void moveUp(float elapsed, float speed = PLAYER_MOVEMENT_SPEED);
		void moveDown(float elapsed, float speed = PLAYER_MOVEMENT_SPEED);
		void stop();
	
		//Possible jump implementation (no real physics simulation here)
		void setHeight(float);
		void jump();
		void rollLeft();
		void rollRight();
		//requestPause(); ???

};