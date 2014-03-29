#include <cmath>

#include "DebugDefinitions.h"
#include "Player.h"
#include "ControllerInputManager.h"
#include "KeyInput.h"
#include "PlayerStatesList.h"

Player::Player(Game& g, int pNum) : Entity(g)
{
	type = EntityType::PLAYER;

	bound->initialize(this);
	
	controller	= g.getControllerManager();
	keyboard	= g.getKeyInput();

	playerNum = pNum;
	for(int i = 0; i < 7; ++i)
		keys[i] = keyboard->playerKeys[playerNum][i];

}

Player::~Player()
{
}

void Player::initialize()
{
	A_FLAG = B_FLAG = X_FLAG = Y_FLAG = LB_FLAG = RB_FLAG = LT_FLAG = RT_FLAG = START_FLAG =  false;

	position.x = 0;
	position.y = 0;
	position.z = 0;
	velocity.x = 0;
	velocity.y = 0;
	lockLeftMovement(false);
	lockRightMovement(false);
	lockForwardMovement(false);
	setDead(false);

	
	while (states.size() > 0 && !containsState(PlayerStateType::PST_REGULAR))
		states.removeFirst();

	moveTo(15.0f, 5.5f - 1.5f * playerNum);
}


void Player::update(float elapsed)
{
	stop();

	if (!containsState(PlayerStateType::PST_INJURED) && !containsState(PlayerStateType::PST_BUMPED))
	{
		if (controller->isConnected(playerNum))
			checkControllerInputs(elapsed);
		else
			checkKeyboardInputs(elapsed);
	}

	for (int i = 0; i < states.size(); ++i)
		states.elementAt(i)->update(elapsed);

	///////////////////
	//Update Position//
	///////////////////
	//Drag
	if(PLAYER_DRAG)
		moveUp(elapsed, ENTITY_DRAG_SPEED/4);

	moveBy(velocity);
}

int Player::getPlayerNum() { return playerNum; }

bool Player::requestingPause()
{
	if (controller->getButtonStart(playerNum))
	{
		if (!START_FLAG)
		{
			START_FLAG = true;
			return true;
		}
	}
	else
		START_FLAG = false;

	return false;

}

///////////////////////
//Collision Functions//
///////////////////////
void Player::onCollide(Player& p, float elapsed)
{
	
	#ifndef PLAYER_COLLIDE_PLAYER_DEBUG
	if (!containsState(PlayerStateType::PST_INJURED))
	{
		//Rolling Collisions
		if (p.containsState(PlayerStateType::PST_ROLL))
		{
			bool rollingLeft;
			for(int i = 0; i < p.states.size(); ++i)
			{
				if (p.states.elementAt(i)->getStateType() == PlayerStateType::PST_ROLL)
				{
					rollingLeft = dynamic_cast<PlayerRollState*>(p.states.elementAt(i))->isRollingLeft();
					break;
				}
			}

			if (!containsState(PlayerStateType::PST_BUMPED))
			{
				addState(*new PlayerBumpState(*this,rollingLeft));
			}

			if (!containsState(PlayerStateType::PST_ROLL))
			{
				addState(*new PlayerInjuredState(*this));
			}
		}
		//Jumping collisions
		else if (p.containsState(PlayerStateType::PST_JUMP))
		{
			//Stomp
			if (!containsState(PlayerStateType::PST_JUMP))
			{
				for(int i = 0; i < p.states.size(); ++i)
				{
					if (p.states.elementAt(i)->getStateType() == PlayerStateType::PST_JUMP)
					{
						if (p.states.elementAt(i)->getProgressPercentage() > 0.5f)
						{
							if (!containsState(PlayerStateType::PST_INJURED))
								addState(*new PlayerInjuredState(*this));
						}
					}
				}
			}
			//Uppercut
			else
			{
				if (p.position.z < position.z)
				{
					for(int i = 0; i < p.states.size(); ++i)
					{
						if (p.states.elementAt(i)->getStateType() == PlayerStateType::PST_JUMP)
						{
							if (p.states.elementAt(i)->getProgressPercentage() < 0.5f)
							{
								if (!containsState(PlayerStateType::PST_INJURED))
									addState(*new PlayerInjuredState(*this));
							}
						}
					}
				}	
			}
		}
		else //two non rolling players
		{
			if (!containsState(PlayerStateType::PST_ROLL))
			{
				
			}
		}
	}
	#endif
}

void Player::onCollide(Obstacle&)
{
	if(PLAYER_COLLIDE_OBSTACLE)
	{
		if (!containsState(PlayerStateType::PST_INJURED))
		{
			addState(*new PlayerInjuredState(*this));
		}
	}
}

////////////////////////////
//State/Listener Functions//
////////////////////////////
//Private
void Player::notifyStateStart(PlayerState& PS)
{
	for (int i = 0; i < listeners.size(); ++i)
	{
		listeners.elementAt(i)->onStateStart(PS);
	}
}
void Player::notifyStateEnd(PlayerState& PS)
{
	for (int i = 0; i < listeners.size(); ++i)
	{
		listeners.elementAt(i)->onStateEnd(PS);
	}
}

//Public
void Player::addListener(IPlayerListener& IPL) { listeners.add(&IPL); }
void Player::removeListener(IPlayerListener& IPL) { listeners.remove(&IPL); }

//Adds PlayerState to states. DOES NOT DO DUPLICATE STATE CHECKING. You must do this before calling addState! Use this: "!containsState(PlayerStateType)"
void Player::addState(PlayerState& PS)
{
	//Loop check through all current PlayerStates (Duplicate testing)
	for(int i = 0; i < states.size(); ++i)
	{
		PlayerState* currentState = states.elementAt(i);
		
		//If there is a PlayerRegularState in here, then get rid of it
		if (currentState->getStateType() == PlayerStateType::PST_REGULAR)
		{
			states.remove(currentState);
			notifyStateEnd(*currentState);
			
			delete currentState;
		}
	}

	states.add(&PS);
	notifyStateStart(PS);
}
void Player::removeState(PlayerState& PS)
{
	states.remove(&PS);
	notifyStateEnd(PS);
	delete &PS;
	if (states.size() == 0)
		states.add(new PlayerRegularState(*this));
}

bool Player::containsState(PlayerStateType PST)
{
	for(int i = 0; i < states.size(); ++i)
		if (states.elementAt(i)->getStateType() == PST) 
			return true;

	return false;
}

/////////////////////
//Input (and Locks)//
/////////////////////
void Player::lockLeftMovement(bool b)    { movementLocks[0] = b; }
void Player::lockRightMovement(bool b)   { movementLocks[1] = b; }
void Player::lockForwardMovement(bool b) { movementLocks[2] = b; }

void Player::checkControllerInputs(float elapsed)
{
	////////////////
	//Stick Checks//
	////////////////
	float LSX = controller->getLS_X(playerNum);
	float LSY = controller->getLS_Y(playerNum);
	if (!containsState(PlayerStateType::PST_ROLL))
	{
		if (LSX < -STICK_MOVEMENT_THRESHOLD)
		{
			moveLeft(elapsed, PLAYER_MOVEMENT_SPEED);
		}
		else if (LSX > STICK_MOVEMENT_THRESHOLD)
		{
			moveRight(elapsed, PLAYER_MOVEMENT_SPEED);
		}
		if (LSY > STICK_MOVEMENT_THRESHOLD)
		{
			moveUp(elapsed, PLAYER_MOVEMENT_SPEED*0.75f);
		}
		else if (LSY < -STICK_MOVEMENT_THRESHOLD)
		{
			moveDown(elapsed, PLAYER_MOVEMENT_SPEED);
		}
	}

	/////////////////
	//Button Checks//
	/////////////////
	if (controller->getButtonA(playerNum))
	{
		if (!A_FLAG)
		{
			A_FLAG = true;
			jump();
		}
	}
	else
		A_FLAG = false;

	if (controller->getButtonB(playerNum))
	{
		if (!B_FLAG)
		{
			B_FLAG = true;
			//Ability?
		}
	}
	else
		B_FLAG = false;

	if (controller->getButtonX(playerNum))
	{
		if (!X_FLAG)
		{
			X_FLAG = true;
			//Ability?
		}
	}
	else
		X_FLAG = false;

	if (controller->getButtonY(playerNum))
	{
		if (!Y_FLAG)
		{
			Y_FLAG = true;
			//Ability?
		}
	}
	else
		Y_FLAG = false;

	//////////////////
	//Trigger Checks//
	//////////////////
	float LT = controller->getLT(playerNum);
	if (LT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		if (!LT_FLAG)
		{
			LT_FLAG = true;
			rollLeft();
		}
	}
	else
		LT_FLAG = false;

	float RT = controller->getRT(playerNum);
	if (RT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		if (!RT_FLAG)
		{
			RT_FLAG = true;
			rollRight();
		}
	}
	else
		RT_FLAG = false;
}

void Player::checkKeyboardInputs(float elapsed)
{
	if (!containsState(PlayerStateType::PST_ROLL))
	{
		if (keyboard->IsKeyDown(keys[0]))
		{
			moveLeft(elapsed);
		}
		else if (keyboard->IsKeyDown(keys[1])) 
		{
			moveRight(elapsed);
		}
		if (keyboard->IsKeyDown(keys[2]))
		{
			moveUp(elapsed);
		}
		else if (keyboard->IsKeyDown(keys[3]))
		{
			moveDown(elapsed);
		}
		if (keyboard->IsKeyDown(keys[4]))
		{
			jump();
		}
	}
	if (!containsState(PlayerStateType::PST_JUMP))
	{
		if (keyboard->IsKeyDown(keys[5]))
		{
			rollLeft();
		}
		if (keyboard->IsKeyDown(keys[6]))
		{
			rollRight();
		}
	}
	
}


//////////////////////
//Movement Functions//
//////////////////////
void Player::moveLeft(float elapsed, float sp)
{
	if (!movementLocks[0])
	{
		velocity.y += sp*elapsed;
		if (movementLocks[1])
			lockRightMovement(false);
	}
}
void Player::moveRight(float elapsed, float sp)
{
	if (!movementLocks[1])
	{
		velocity.y += -sp*elapsed;
		if (movementLocks[0])
				lockLeftMovement(false);
	}
}
void Player::moveUp(float elapsed, float sp)
{
	velocity.x += -sp*elapsed;
	if (movementLocks[2])
		lockForwardMovement(false);
}
void Player::moveDown(float elapsed, float sp)
{
	if (!movementLocks[2])
	{
		velocity.x += sp*elapsed;
	}
}


void Player::stop()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Player::jump()
{
	if (!containsState( PlayerStateType::PST_JUMP ))
		addState( *(new PlayerJumpState(*this)) );
}

void Player::rollLeft()
{
	if (!containsState( PlayerStateType::PST_ROLL ))
		addState( *(new PlayerRollState(*this, true)) );
}
void Player::rollRight()
{
	if (!containsState( PlayerStateType::PST_ROLL ))
		addState( *(new PlayerRollState(*this, false)) );
}

void Player::setHeight(float height)
{
	position.z = height;
}