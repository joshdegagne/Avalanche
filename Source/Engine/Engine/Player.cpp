#include "Player.h"
#include "DebugConsole.h"

Player::Player(Game& g, int pNum) : Entity()
{

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
	}
	else if (playerNum == 1) //Player two (WASD)
	{
		keys[0] = ascii_A;
		keys[1] = ascii_D;
		keys[2] = ascii_W;
		keys[3] = ascii_S;
	}
	else if (playerNum == 2) //Player three (TFGH)
	{
		keys[0] = ascii_F;
		keys[1] = ascii_H;
		keys[2] = ascii_T;
		keys[3] = ascii_G;
	}
	else if (playerNum == 3) //Player four (IJKL)
	{
		keys[0] = ascii_J;
		keys[1] = ascii_L;
		keys[2] = ascii_I;
		keys[3] = ascii_K;
	}

	position.x = 0;
	position.y = 0;
	position.z = 0;
	velocity.x = 0;
	velocity.y = 0;
	jumpIncrement = 0.0f;
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

GameModel* Player::getPlayerModel()
{
	return playerModel;
}

void Player::update(float elapsed)
{
	//Needed: 
	//  - implementation/usage of "elapsed"
	//  - Prioritization of actions?
	//	- Check for buttons being released?

	stop();

	if (controller->isConnected(playerNum))
		checkControllerInputs();
	else
		checkKeyboardInputs();

	///////////////////
	//Update Position//
	///////////////////
	moveBy(velocity, elapsed * MOVEMENT_SPEED);

	//position.x += velocity.x * elapsed;
	//position.y += velocity.y * elapsed;
	//playerModel->worldTranslate(velocity.x, velocity.y, 0.0f);
}

void Player::render()
{
}

void Player::checkControllerInputs()
{
	////////////////
	//Stick Checks//
	////////////////
	float LSX = controller->getLS_X(playerNum);
	float LSY = controller->getLS_Y(playerNum);
	if (LSX > STICK_MOVEMENT_THRESHOLD)
	{
		//moveRight();
	}
	else if (LSX < -STICK_MOVEMENT_THRESHOLD)
	{
		//moveLeft();
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

void Player::checkKeyboardInputs()
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
}


void Player::moveLeft()
{
	velocity.y = 1;
}
void Player::moveRight()
{
	velocity.y = -1;
}
void Player::moveDown()
{
	velocity.x = 1;
}
void Player::moveUp()
{
	velocity.x = -1;
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