#include "Player.h"
#include "DebugConsole.h"

Player::Player(Game& g, int pNum) : Entity()
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
		keys[4] = VK_SPACE;
	}
	else if (playerNum == 1) //Player two (WASD)
	{
		keys[0] = ascii_A;
		keys[1] = ascii_D;
		keys[2] = ascii_W;
		keys[3] = ascii_S;
		keys[4] = 0;
	}
	else if (playerNum == 2) //Player three (TFGH)
	{
		keys[0] = ascii_F;
		keys[1] = ascii_H;
		keys[2] = ascii_T;
		keys[3] = ascii_G;
		keys[4] = 0;
	}
	else if (playerNum == 3) //Player four (IJKL)
	{
		keys[0] = ascii_J;
		keys[1] = ascii_L;
		keys[2] = ascii_I;
		keys[3] = ascii_K;
		keys[4] = 0;
	}

	position.x = 0;
	position.y = 0;
	position.z = 0;
	velocity.x = 0;
	velocity.y = 0;
	lockLeftMovement(false);
	lockRightMovement(false);
	lockForwardMovement(false);
	jumpIncrement = 0.0f;

	moveTo(1.0f, 1.0f);
}

Player::~Player()
{
	if (playerModel)
	{
		delete playerModel;
		playerModel = 0;
	}

	if (keyboard)
	{
		delete keyboard;
		keyboard = 0;
	}
}

GameModel* Player::getPlayerModel() { return playerModel; }
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

	///////////////////
	//Update Position//
	///////////////////
	moveBy(velocity, elapsed * MOVEMENT_SPEED);
	jumpArc(elapsed);
	//position.x += velocity.x * elapsed;
	//position.y += velocity.y * elapsed;
	//playerModel->worldTranslate(velocity.x, velocity.y, 0.0f);
}

void Player::render()
{
}

void Player::lockLeftMovement(bool b)    { movementLocks[0] = b; writeLabelToConsole(L"Movement locked for player ", playerNum);}
void Player::lockRightMovement(bool b)   { movementLocks[1] = b; writeLabelToConsole(L"Movement locked for player ", playerNum);}
void Player::lockForwardMovement(bool b) { movementLocks[2] = b; writeLabelToConsole(L"Movement locked for player ", playerNum);}

void Player::checkControllerInputs(float elapsed)
{
	////////////////
	//Stick Checks//
	////////////////
	float LSX = controller->getLS_X(playerNum);
	float LSY = controller->getLS_Y(playerNum);
	if (LSX < -STICK_MOVEMENT_THRESHOLD)
	{
		//moveLeft();
	}
	else if (LSX > STICK_MOVEMENT_THRESHOLD)
	{
		//moveRight();
	}
	if (LSY > STICK_MOVEMENT_THRESHOLD)
	{
		//moveUp();
	}
	else if (LSY < -STICK_MOVEMENT_THRESHOLD)
	{
		//moveDown();
	}

	/////////////////
	//Button Checks//
	/////////////////
	if (controller->getButtonA(playerNum))
	{
		//jump();
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
		//Roll left?
	}

	float RT = controller->getRT(playerNum);
	if (RT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		//Roll right?
	}
}

void Player::checkKeyboardInputs(float elapsed)
{
	if (keyboard->IsKeyDown(keys[0]))
	{
		moveLeft();
	}
	else if (keyboard->IsKeyDown(keys[1])) 
	{
		moveRight();
	}
	if (keyboard->IsKeyDown(keys[2]))
	{
		moveUp();
	}
	else if (keyboard->IsKeyDown(keys[3]))
	{
		moveDown();
	}
	if (keyboard->IsKeyDown(keys[4]))
	{
		jump(elapsed);
	}
}


void Player::moveLeft()
{
	if (!movementLocks[0])
	{
		velocity.y = 1;
		if (movementLocks[1])
			lockRightMovement(false);
	}
}
void Player::moveRight()
{
	if (!movementLocks[1])
	{
		velocity.y = -1;
		if (movementLocks[0])
				lockLeftMovement(false);
	}
}
void Player::moveUp()
{
	velocity.x = -1;
	if (movementLocks[2])
		lockForwardMovement(false);
}
void Player::moveDown()
{
	if (!movementLocks[2])
	velocity.x = 1;
}


void Player::stop()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Player::jump(float elapsed)
{
	
	if (jumpIncrement == 0.0f)
	{
		jumpIncrement = elapsed;
	}
}

void Player::jumpArc(float elapsed)
{
	if (jumpIncrement > 0.0f && jumpIncrement < 4.0f)
	{
		jumpIncrement += elapsed;
		float arc = (-1*(jumpIncrement - 2)*(jumpIncrement - 2))+4; //parabola

		position.z += arc;
		playerModel->worldTranslate(0.0f, 0.0f, arc);
	}
	else
	{
		jumpIncrement = 0.0f;
		position.z = 0;
	}
}