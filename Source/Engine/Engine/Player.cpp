#include "Player.h"
#include "DebugConsole.h"

Player::Player(Game& g, int pNum) : Entity()
{
	controller = g.getControllerManager();
	keyboard   = g.getKeyInput();
	playerNum = pNum;
	position.x = 0;
	position.y = 0;
	velocity.x = 0;
	velocity.y = 0;

	// constructing gamemodel here to simply test out the drawing and movement
	WCHAR* iceClimberHeadTexture = L"textures/iceclimberhead.dds";
	playerModel = new PlayerModel(1.0f, 1.0f, iceClimberHeadTexture);
}

Player::~Player()
{
	delete playerModel;
	playerModel = 0;
}

GameModel* Player::getPlayerModel()
{
	return playerModel;
}

void Player::render()
{
}

void Player::update(float elapsed)
{
	//Needed: 
	//  - implementation/usage of "elapsed"
	//  - Prioritization of actions?
	//	- Check for buttons being released?

	stop();

	////////////////////////////
	//Keyboard Movement Checks//
	////////////////////////////
	if (playerNum == 0) //Player one (Arrow Keys)
	{
		if (keyboard->IsKeyDown(VK_LEFT))
		{
			moveLeft();
		}
		else if (keyboard->IsKeyDown(VK_RIGHT)) 
		{
			moveRight();
		}
		if (keyboard->IsKeyDown(VK_UP))
		{
			moveUp();
		}
		else if (keyboard->IsKeyDown(VK_DOWN))
		{
			moveDown();
		}
	}
	if (playerNum == 1) //Player two (WASD)
	{
		if (keyboard->IsKeyDown(ascii_A))
		{
			moveLeft();
		}
		else if (keyboard->IsKeyDown(ascii_D)) 
		{
			moveRight();
		}
		if (keyboard->IsKeyDown(ascii_W))
		{
			moveUp();
		}
		else if (keyboard->IsKeyDown(ascii_S))
		{
			moveDown();
		}
	}
	if (playerNum == 2) //Player three (TFGH)
	{
		if (keyboard->IsKeyDown(ascii_F))
		{
			moveLeft();
		}
		else if (keyboard->IsKeyDown(ascii_H)) 
		{
			moveRight();
		}
		if (keyboard->IsKeyDown(ascii_T))
		{
			moveUp();
		}
		else if (keyboard->IsKeyDown(ascii_G))
		{
			moveDown();
		}
	}
	if (playerNum == 3) //Player four (IJKL)
	{
		if (keyboard->IsKeyDown(ascii_J))
		{
			moveLeft();
		}
		else if (keyboard->IsKeyDown(ascii_L)) 
		{
			moveRight();
		}
		if (keyboard->IsKeyDown(ascii_I))
		{
			moveUp();
		}
		else if (keyboard->IsKeyDown(ascii_K))
		{
			moveDown();
		}
	}

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
		//Jump?
		return;
	}
	if (controller->getButtonB(playerNum))
	{
		//Ability?
		return;
	}
	if (controller->getButtonX(playerNum))
	{
		//Ability?
		return;
	}
	if (controller->getButtonY(playerNum))
	{
		//Ability?
		return;
	}
	if (controller->getButtonLB(playerNum))
	{
		//Roll left? Or would that be LT?
		return;
	}
	if (controller->getButtonRB(playerNum))
	{
		//Roll right? Or would that be RT?
		return;
	}
	if (controller->getButtonStart(playerNum))
	{
		//Pause game?
		return;
	}
	if (controller->getButtonBack(playerNum))
	{
		//????
		return;
	}

	//////////////////
	//Trigger Checks//
	//////////////////
	float LT = controller->getLT(playerNum);
	if (LT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		//Roll left?
		return;
	}

	float RT = controller->getRT(playerNum);
	if (RT > TRIGGER_ACTIVATION_THRESHOLD)
	{
		//Roll right?
		return;
	}

	///////////////////
	//Update Position//
	///////////////////
	position.x += velocity.x;
	position.y += velocity.y;
	playerModel->worldTranslate(velocity.x, velocity.y, 0.0f);
}

void Player::moveLeft()
{
	velocity.y = MOVEMENT_SPEED;
}
void Player::moveRight()
{
	velocity.y = -MOVEMENT_SPEED;
}
void Player::moveDown()
{
	velocity.x = MOVEMENT_SPEED;
}
void Player::moveUp()
{
	velocity.x = -MOVEMENT_SPEED;
}

void Player::stop()
{
	velocity.x = 0;
	velocity.y = 0;
}