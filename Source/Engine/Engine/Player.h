#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player: public Entity {
	public: 
		//Constructors
		Player();
		
		void update(float);

	private:
		int playerNum; //This was created for use with the ControllerInputManager. Valid nums are [0-3]

};
#endif