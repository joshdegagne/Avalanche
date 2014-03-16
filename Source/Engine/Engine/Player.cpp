#include <cmath>

#include "Player.h"
#include "ControllerInputManager.h"
#include "KeyInput.h"
#include "PlayerStatesList.h"

#include "DebugDefinitions.h"

Player::Player(Game& g, int pNum) : Entity(g)
{
	type = EntityType::PLAYER;

	bound->initialize(this);

	writeLabelToConsole(L"Bottom of the player's bounding box: ",bound->getPosition()->z);

	controller	= g.getControllerManager();
	keyboard	= g.getKeyInput();

	playerNum = pNum;
	if (playerNum == 0) //Player one (Arrow Keys)
	{
		keys[0] = VK_LEFT;
		keys[1] = VK_RIGHT;
		keys[2] = VK_UP;
		keys[3] = VK_DOWN;
		keys[4] = 0;
		keys[5] = 0;
		keys[6] = 0;
	}
	else if (playerNum == 1) //Player two (WASD)
	{
		keys[0] = ascii_A;
		keys[1] = ascii_D;
		keys[2] = ascii_W;
		keys[3] = ascii_S;
		keys[4] = VK_SPACE;
		keys[5] = ascii_Q;
		keys[6] = ascii_E;
	}
	else if (playerNum == 2) //Player three (TFGH)
	{
		keys[0] = ascii_F;
		keys[1] = ascii_H;
		keys[2] = ascii_T;
		keys[3] = ascii_G;
		keys[4] = 0;
		keys[5] = 0;
		keys[6] = 0;
	}
	else if (playerNum == 3) //Player four (IJKL)
	{
		keys[0] = ascii_J;
		keys[1] = ascii_L;
		keys[2] = ascii_I;
		keys[3] = ascii_K;
		keys[4] = 0;
		keys[5] = ascii_U;
		keys[6] = ascii_O;
	}

	A_FLAG = B_FLAG = X_FLAG = Y_FLAG = LB_FLAG = RB_FLAG = LT_FLAG = RT_FLAG =  false;

	position.x = 0;
	position.y = 0;
	position.z = 0;
	velocity.x = 0;
	velocity.y = 0;
	speed = 0;
	lockLeftMovement(false);
	lockRightMovement(false);
	lockForwardMovement(false);
	jumpIncrement = 0.0f;

	addState(*(new PlayerRegularState(*this)));

	moveTo(5.0f, 0.75f + 1.5f * playerNum);
}

Player::~Player()
{
}

int Player::getPlayerNum() { return playerNum; }

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
	moveBy(velocity, speed);

	#ifndef PLAYER_DRAG_DEBUG
	float dragSpeed = MOVEMENT_SPEED*elapsed/4;
	if(containsState(PlayerStateType::PST_INJURED))
		dragSpeed*=6;
	if(position.x != DEAD_X && position.y != DEAD_Y)
		moveBy(XMFLOAT2(-1.0f, 0.0f), dragSpeed);
	#endif
}

void Player::render()
{
}

///////////////////////
//Collision Functions//
///////////////////////
void Player::onCollide(Player& p)
{
	#ifndef PLAYER_COLLIDE_PLAYER_DEBUG
	if (!containsState(PlayerStateType::PST_INJURED))
	{
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
		else //two non rolling players
		{
			//This is absolutely not working correctly, and should only be implemented once properly complete.
			/*
			if (!containsState(PlayerStateType::PST_ROLL))
			{
				while (std::abs(p.getPosition().x-position.x) < bound->getDimensions()->x)
				{
					if(p.getPosition().x < position.x)
					{
						position.x += 0.1f;
					}
					else
					{
						position.x -= 0.1f;
					}
				}
				while (std::abs(p.getPosition().y-position.y) < bound->getDimensions()->y)
				{
					if(p.getPosition().y < position.y)
					{
						position.y += 0.1f;
					}
					else
					{
						position.y -= 0.1f;
					}
				}
			}
			*/
		}
	}
	#endif
}

void Player::onCollide(Obstacle&)
{
	#ifndef PLAYER_COLLIDE_OBSTACLE_DEBUG
	if (!containsState(PlayerStateType::PST_INJURED))
	{
		addState(*new PlayerInjuredState(*this));
	}
	#endif
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
			delete currentState;
		}
	}

	states.add(&PS);
}
void Player::removeState(PlayerState& PS)
{
	states.remove(&PS);
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
			moveLeft(elapsed);
		}
		else if (LSX > STICK_MOVEMENT_THRESHOLD)
		{
			moveRight(elapsed);
		}
		if (LSY > STICK_MOVEMENT_THRESHOLD)
		{
			moveUp(elapsed);
		}
		else if (LSY < -STICK_MOVEMENT_THRESHOLD)
		{
			moveDown(elapsed);
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

	if (controller->getButtonLB(playerNum))
	{
		if (!LB_FLAG)
		{
			LB_FLAG = true;
			rollLeft();
		}
	}
	else
		LB_FLAG = false;

	if (controller->getButtonRB(playerNum) && !RB_FLAG)
	{
		if (!RB_FLAG)
		{
			RB_FLAG = true;
			rollRight();
		}
	}
	else
		RB_FLAG = false;

	if (controller->getButtonStart(playerNum))
	{
		//Pause game?
	}
	if (controller->getButtonBack(playerNum))
	{
		//????
	}

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
		speed = sp*elapsed;
		velocity.y = speed;
		if (movementLocks[1])
			lockRightMovement(false);
	}
}
void Player::moveRight(float elapsed, float sp)
{
	if (!movementLocks[1])
	{
		speed = sp*elapsed;
		velocity.y = -speed;
		if (movementLocks[0])
				lockLeftMovement(false);
	}
}
void Player::moveUp(float elapsed, float sp)
{
	speed = sp*elapsed;
	velocity.x = -speed;
	if (movementLocks[2])
		lockForwardMovement(false);
}
void Player::moveDown(float elapsed, float sp)
{
	if (!movementLocks[2])
	{
		speed = sp*elapsed;
		velocity.x = speed;
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

void Player::jumpArc(float elapsed)
{
	if (jumpIncrement > 0.0f && jumpIncrement < 4.0f)
	{
		jumpIncrement += elapsed;
		float arc = (-1*(jumpIncrement - 2)*(jumpIncrement - 2))+4; //parabola

		position.z += arc;
	}
	else
	{
		jumpIncrement = 0.0f;
		position.z = 0;
	}
}