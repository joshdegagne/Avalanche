#include "MenuManager.h"
#include "Game.h"
#include "ControllerInputManager.h"
#include "KeyInput.h"
#include "ModelManager.h"
#include "AudioManager.h"
#include "MainMenu.h"
#include "PlayerSelectMenu.h"
#include "PauseMenu.h"
#include "ResultsMenu.h"
#include "ControlsMenu.h"
#include "CreditsMenu.h"
#include "MainMenuViewModel.h"
#include "PlayerSelectMenuView.h"
#include "ResultsMenuView.h"
#include <vector>

#include "DebugDefinitions.h"

MenuManager::~MenuManager()
{
	delete mainMenu;
	delete playerSelectMenu;
	delete pauseMenu;
	delete controlsMenu;
	delete creditsMenu;
}

bool MenuManager::initialize(Game& g)
{
	game = &g;

	mainMenu		 = new MainMenu(this);
	playerSelectMenu = new PlayerSelectMenu(this);
	pauseMenu		 = new PauseMenu(this);
	resultsMenu		 = new ResultsMenu(this);
	controlsMenu	 = new ControlsMenu(this);
	creditsMenu		 = new CreditsMenu(this);

	mainMenuView	 = new MainMenuViewModel(g);
	playerSelectView = new PlayerSelectMenuView(g);
	resultsView		 = new ResultsMenuView(g);


	//game->getModelManager()->add(*mainMenu);
	//game->getModelManager()->add(*pauseMenu);
	//game->getModelManager()->add(*controlsMenu);
	//game->getModelManager()->add(*creditsMenu);

	controlPlayer = 0;
	UP_FLAG = DOWN_FLAG = CONFIRM_FLAG = CLOSE_FLAG = false;

	addMainMenu();

	return true;
}

void MenuManager::update(float elapsedTime)
{
	if (menuOrderStack.empty())
		return;

	////////////////////
	//Controller Input//
	////////////////////
	ControllerInputManager* controller = game->getControllerManager();
	
	if (controller->isConnected(controlPlayer))
	{
		////////////////
		//Stick Checks//
		////////////////
		float LSY = controller->getLS_Y(controlPlayer);
		if (LSY > STICK_MOVEMENT_THRESHOLD)
		{
			if (!UP_FLAG)
			{
				if (MENU_DEBUG)
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
				if (MENU_DEBUG)
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
		if (controller->getButtonA(controlPlayer))
		{
			if (!CONFIRM_FLAG)
			{
				if (MENU_DEBUG)
					writeTextToConsole(L"CONFIRM!");

				CONFIRM_FLAG = true;
				menuOrderStack.top()->confirmSelection();
			}
		}
		else
			CONFIRM_FLAG = false;

		if (controller->getButtonB(controlPlayer))
		{
			if (!CLOSE_FLAG)
			{
				if (MENU_DEBUG)
					writeTextToConsole(L"CLOSE!");

				CLOSE_FLAG = true;
				if (menuOrderStack.top() != mainMenu)
					removeCurrentMenu();
			}
		}
		else
			CLOSE_FLAG = false;
	}
	/////////////
	//Key Input//
	/////////////
	else
	{
		KeyInput* keyboard = game->getKeyInput();
		
			if (keyboard->IsKeyDown(keyboard->playerKeys[controlPlayer][2])) //UP
			{
				if(!UP_FLAG)
				{
					if (MENU_DEBUG)
						writeTextToConsole(L"UP!");

					UP_FLAG = true;
					menuOrderStack.top()->scrollUp();
				}
			}
			else
				UP_FLAG = false;
			if (keyboard->IsKeyDown(keyboard->playerKeys[controlPlayer][3])) //DOWN
			{
				if(!DOWN_FLAG)
				{
					if (MENU_DEBUG)
						writeTextToConsole(L"DOWN!");

					DOWN_FLAG = true;
					menuOrderStack.top()->scrollDown();
				}
			}
			else
				DOWN_FLAG = false;
			if (keyboard->IsKeyDown(keyboard->playerKeys[controlPlayer][4])) //CONFIRM
			{
				if(!CONFIRM_FLAG)
				{
					if (MENU_DEBUG)
						writeTextToConsole(L"CONFIRM!");

					CONFIRM_FLAG = true;
					menuOrderStack.top()->confirmSelection();
				}
			}
			else
				CONFIRM_FLAG = false;
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
	menuOrderStack.top()->resetSelection();
	menuOrderStack.pop();
	if (!menuOrderStack.empty())
		menuOrderStack.top()->setActive(true);
	
	if (MENU_DEBUG)
		writeTextToConsole(L"CURRENT MENU REMOVED");
}
void MenuManager::removeAllMenus()
{
	while (!menuOrderStack.empty())
		removeCurrentMenu();
}
void MenuManager::addMainMenu()
{
	if (MENU_DEBUG)
		writeTextToConsole(L"MAIN MENU ADDED");
	addMenu(mainMenu);
	game->getAudioManager()->StopSong01();
}
void MenuManager::addPlayerSelectMenu()
{
	if (PLAYER_NUMBER_OVERRIDE)
	{
		sendStartGameSignal((int)PLAYER_NUMBER_OVERRIDE);
	}
	else
	{
		if (MENU_DEBUG)
			writeTextToConsole(L"PLAYER SELECT MENU ADDED");
		addMenu(playerSelectMenu);
	}
}
void MenuManager::addPauseMenu(int requestPlayerNumber)
{
	if (MENU_DEBUG)
		writeLabelToConsole(L"PAUSE MENU ADDED FOR PLAYER ", requestPlayerNumber);

	controlPlayer = requestPlayerNumber;
	addMenu(pauseMenu);
}
void MenuManager::addResultsMenu(std::vector<bool> s)
{
	if (MENU_DEBUG)
		writeTextToConsole(L"RESULTS MENU ADDED");

	resultsMenu->setSurvivors(s);
	addMenu(resultsMenu);
}
void MenuManager::addControlsMenu()
{
	if (MENU_DEBUG)
		writeTextToConsole(L"CONTROLS MENU ADDED");

	addMenu(controlsMenu);
}
void MenuManager::addCreditsMenu()
{
	if (MENU_DEBUG)
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

//////////////////////////////
//Signals from Menus to Game//
//////////////////////////////
void MenuManager::sendStartGameSignal(int numPlayers)
{
	removeAllMenus();
	game->HandleStartGameSignal(numPlayers);
}
void MenuManager::sendEndGameSignal()
{
	game->HandleEndGameSignal(0);
}
void MenuManager::sendEndProgramSignal()
{
	game->HandleEndProgramSignal();
}
void MenuManager::sendUnPauseSignal()
{
	removeAllMenus();
	controlPlayer = 0;
	game->HandleUnPauseSignal();
}

void MenuManager::draw(Game& g)
{
	mainMenuView->Draw(mainMenu);
	playerSelectView->Draw(playerSelectMenu);
	resultsView->Draw(resultsMenu);


	//g.getGraphics()->getD3D()->getSwapChain()->Present(0,0);
}

void MenuManager::shutdown()
{
	
}