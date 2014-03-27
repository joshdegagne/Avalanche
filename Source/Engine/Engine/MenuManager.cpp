#include "MenuManager.h"
#include "Game.h"
#include "ControllerInputManager.h"
#include "ModelManager.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "ControlsMenu.h"
#include "CreditsMenu.h"


#include "DebugDefinitions.h"

bool MenuManager::initialize(Game& g)
{
	game = &g;

	mainMenu	 = new MainMenu(this);
	pauseMenu	 = new PauseMenu(this);
	controlsMenu = new ControlsMenu(this);
	creditsMenu	 = new CreditsMenu(this);
	//game->getModelManager()->add(*mainMenu);
	//game->getModelManager()->add(*pauseMenu);
	//game->getModelManager()->add(*controlsMenu);
	//game->getModelManager()->add(*creditsMenu);

	UP_FLAG = DOWN_FLAG = CONFIRM_FLAG = CLOSE_FLAG = false;

	addMainMenu();
	writeLabelToConsole(L"Added Main Menu!", (int)menuOrderStack.size());

	return true;
}

void MenuManager::update(float elapsedTime)
{
	
	//writeLabelToConsole(L"Number of Menus: ", (int)menuOrderStack.size());
	if (menuOrderStack.empty())
		return;


	ControllerInputManager* controller = game->getControllerManager();
	for (int i = 0; i < 1; ++i)
	{
		////////////////
		//Stick Checks//
		////////////////
		float LSY = controller->getLS_Y(i);
		if (LSY > STICK_MOVEMENT_THRESHOLD)
		{
			if (!UP_FLAG)
			{
				writeTextToConsole(L"UP!");
				UP_FLAG = true;
				menuOrderStack.top()->scrollUp();
			}
		}
		else
			UP_FLAG = false;

		if (LSY < -STICK_MOVEMENT_THRESHOLD)
		{
			if (!DOWN_FLAG)
			{
				writeTextToConsole(L"DOWN!");
				DOWN_FLAG = true;
				menuOrderStack.top()->scrollDown();
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
				writeTextToConsole(L"CONFIRM!");
				CONFIRM_FLAG = true;
				menuOrderStack.top()->confirmSelection();
			}
		}
		else
			CONFIRM_FLAG = false;

		if (controller->getButtonB(i) || controller->getButtonBack(i))
		{
			if (!CLOSE_FLAG)
			{
				writeTextToConsole(L"CLOSE!");
				CLOSE_FLAG = true;
				if (menuOrderStack.top() != mainMenu)
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

	menuOrderStack.top()->setActive(false);
	menuOrderStack.pop();
	if (!menuOrderStack.empty())
		menuOrderStack.top()->setActive(true);
	
	writeTextToConsole(L"CURRENT MENU REMOVED");
}
void MenuManager::addMainMenu()
{
	writeTextToConsole(L"MAIN MENU ADDED");
	addMenu(mainMenu);
}
void MenuManager::addPauseMenu()
{
	writeTextToConsole(L"PAUSE MENU ADDED");
	addMenu(pauseMenu);
}
void MenuManager::addControlsMenu()
{
	writeTextToConsole(L"CONTROLS MENU ADDED");
	addMenu(controlsMenu);
}
void MenuManager::addCreditsMenu()
{
	writeTextToConsole(L"CREDITS MENU ADDED");
	addMenu(creditsMenu);
}
void MenuManager::addMenu(Menu* newMenu)
{
	if(!menuOrderStack.empty())
		menuOrderStack.top()->setActive(false);
	menuOrderStack.push(newMenu);
	menuOrderStack.top()->setActive(true);
}

///////////////////
//Signals to Game//
///////////////////
void MenuManager::sendStartGameSignal()
{
	removeCurrentMenu();
	game->HandleStartGameSignal();
}
void MenuManager::sendEndGameSignal()
{
	game->HandleEndGameSignal();
}
void MenuManager::sendEndProgramSignal()
{
	game->HandleEndProgramSignal();
}