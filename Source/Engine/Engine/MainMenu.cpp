///////////////////////////////////////////////////////////////////////////////
// Filename: MainMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "MainMenu.h"
#include "MenuManager.h"


MainMenu::MainMenu(MenuManager* menuMan, bool activity)
{
	menuManager = menuMan;
	active = activity;
	selection = 0;
	numSelections = 4;
	entityType = EntityType::MENU;
}

void MainMenu::confirmSelection()
{
	switch(selection)
	{
	case 0: menuManager->sendStartGameSignal(); // Start Game
			break;
	case 1: menuManager->addControlsMenu(); // Controls
			break;
	case 2: menuManager->addCreditsMenu(); // Credits
			break; 
	case 3: menuManager->sendEndProgramSignal(); // Exit Program
			break;
	}
}