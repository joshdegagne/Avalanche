#include "MenuManager.h"
#include "Game.h"
#include "ControllerInputManager.h"
#include "ModelManager.h"

#include "DebugDefinitions.h"

bool MenuManager::initialize(Game& g)
{
	game = &g;

	//game->getModelManager()->add(*mainMenu);
	//game->getModelManager()->add(*pauseMenu);
	//game->getModelManager()->add(*controlsMenu);
	//game->getModelManager()->add(*creditsMenu);

	UP_FLAG = DOWN_FLAG = CONFIRM_FLAG = CLOSE_FLAG = false;

	return true;
}

void MenuManager::update(float elapsedTime)
{
	if (menuOrderStack.empty())
		return;

	ControllerInputManager* controller;
	for (int i = 0; i < game->GetPlayers()->size(); ++i)
	{
		////////////////
		//Stick Checks//
		////////////////
		float LSY = controller->getLS_Y(i);
		if (LSY > STICK_MOVEMENT_THRESHOLD)
		{
			if (!UP_FLAG)
			{
				UP_FLAG = true;
				//menuOrderStack.top()->scrollUp();
			}
		}
		else
			UP_FLAG = false;

		if (LSY < -STICK_MOVEMENT_THRESHOLD)
		{
			if (!DOWN_FLAG)
			{
				DOWN_FLAG = true;
				//menuOrderStack.top()->scrollDown();
			}
		}
		else
			DOWN_FLAG = false;

		/////////////////
		//Button Checks//
		/////////////////
		if (controller->getButtonA(i) || controller->getButtonStart(i))
		{
			if (!CONFIRM_FLAG)
			{
				CONFIRM_FLAG = true;
				//menuOrderStack.top()->confirmSelection();
			}
		}
		else
			CONFIRM_FLAG = false;

		if (controller->getButtonB(i) || controller->getButtonBack(i))
		{
			if (!CLOSE_FLAG)
			{
				CLOSE_FLAG = true;
				removeCurrentMenu();
			}
		}
		else
			CLOSE_FLAG = false;
	}
}

///////////////////////////
//Menu Control Management//
///////////////////////////
void MenuManager::removeCurrentMenu()
{
	if (menuOrderStack.empty())
		return;

	//menuOrderStack.top()->setActive(false);
	menuOrderStack.pop();
	if (!menuOrderStack.empty())
		{/*menuOrderStack.top()->setActive(true);*/}
}
void MenuManager::addMainMenu()
{
	//menuOrderStack.push(mainMenu);
}
void MenuManager::addPauseMenu()
{
	//menuOrderStack.push(pauseMenu);
}
void MenuManager::addControlsMenu()
{
	//menuOrderStack.push(controlsMenu);
}
void MenuManager::addCreditsMenu()
{
	//menuOrderStack.push(creditsMenu);
}

///////////////////
//Signals to Game//
///////////////////
void MenuManager::sendStartGameSignal()
{
}
void MenuManager::sendEndGameSignal()
{
}
void MenuManager::sendEndProgramSignal()
{
}