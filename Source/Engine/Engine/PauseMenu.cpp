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
}

void PauseMenu::confirmSelection()
{
	switch(selection)
	{
	case 0: menuManager->removeCurrentMenu(); // Resume
			break;
	case 1: menuManager->addControlsMenu(); // Controls
			break;
	case 2: menuManager->sendEndGameSignal(); // Exit Program
			break;
	}
}