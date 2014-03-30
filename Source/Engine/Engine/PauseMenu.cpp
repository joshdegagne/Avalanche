///////////////////////////////////////////////////////////////////////////////
// Filename: PauseMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PauseMenu.h"
#include "MenuManager.h"

PauseMenu::PauseMenu(MenuManager* menuMan, bool activity)
{
	menuManager = menuMan;
	active = activity;
	selection = 0;
	numSelections = 3;
	entityType = EntityType::MENU;
	pausedPlayer = 0;
}

void PauseMenu::confirmSelection()
{
	switch(selection)
	{
	case 0: menuManager->sendUnPauseSignal();	// Resume
			break;
	case 1: menuManager->addControlsMenu();		// Controls
			break;
	case 2: menuManager->sendEndGameSignal();	// Exit Program
			break;
	}
}

int PauseMenu::getPausedPlayer() { return pausedPlayer; }
void PauseMenu::setPausedPlayer(int p) { pausedPlayer = p; }