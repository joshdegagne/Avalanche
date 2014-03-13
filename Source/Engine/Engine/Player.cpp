#include "Player.h"
#include "ControllerInputManager.h"
#include "KeyInput.h"
#include "PlayerStatesList.h"

#include "DebugConsole.h"

Player::Player(Game& g, int pNum) : Entity(g)
{
	type = EntityType::PLAYER;

	bound->initialize(this);

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
		keys[5] = 0;
		keys[6] = 0;
	}

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

	moveTo(1.0f, 1.0f);
}

Player::~Player()
{
}

int Player::getPlayerNum() { return playerNum; }

void Player::update(float elapsed)
{
	//writeLabelToConsole(L"Elapsed time: ", elapsed);
	//Needed: 
	//  - Prioritization of actions?
	//	- Check for buttons being released?

	stop();

	if (controller->isConnected(playerNum))
		checkControllerInputs(elapsed);
	else
		checkKeyboardInputs(elapsed);

	for (int i = 0; i < states.size(); ++i)
		states.elementAt(i)->update(elapsed);

	///////////////////
	//Update Position//
	///////////////////
	moveBy(velocity, speed);
	//jumpArc(elapsed);
	//position.x += velocity.x * elapsed;
	//position.y += velocity.y * elapsed;
	//playerModel->worldTranslate(velocity.x, velocity.y, 0.0f);
}

void Player::render()
{
}

///////////////////////
//Collision Functions//
///////////////////////
void Player::onCollide(Player&)
{
}

void Player::onCollide(Obstacle&)
{
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

//CURRENTLY INEFFICIENT. DUPLICATE TESTING SHOULD BE DONE BEFORE WE REACH THIS POINT!
void Player::addState(PlayerState& PS)
{
	//Loop check through all current PlayerStates (Duplicate testing)
	for(int i = 0; i < states.size(); ++i)
	{
		PlayerState* currentState = states.elementAt(i);
		
		//If we already have one of this type, return and don't add. We don't want two of the same PlayerState!
		if (currentState->getStateType() == PS.getStateType())
		{
			delete &PS;
			return;
		}

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
		jump();
	}
	if (controller->getButtonB(playerNum))
	{
		//Ability?
	}
	if (controller->getButtonX(playerNum))
	{
		//Ability?
	}
	if (controller->getButtonY(playerNum))
	{
		//Ability?
	}
	if (controller->getButtonLB(playerNum))
	{
		//Roll left? Or would that be LT?
	}
	if (controller->getButtonRB(playerNum))
	{
		//Roll right? Or would that be RT?
	}
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
		rollLeft();
	}

	float RT = controller->getRT(playerNum);
	if (RT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		rollRight();
	}
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
	}
	if (keyboard->IsKeyDown(keys[4]))
	{
		jump();
	}
	if (keyboard->IsKeyDown(keys[5]))
	{
		rollLeft();
	}
	if (keyboard->IsKeyDown(keys[6]))
	{
		rollRight();
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