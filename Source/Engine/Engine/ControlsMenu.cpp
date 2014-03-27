///////////////////////////////////////////////////////////////////////////////
// Filename: ControlsMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ControlsMenu.h"
#include "MenuManager.h"

ControlsMenu::ControlsMenu(MenuManager* menuMan, bool activity)
{
	menuManager = menuMan;
	active = activity;
	selection = 0;
	numSelections = 0;
}

void ControlsMenu::confirmSelection()
{
	menuManager->removeCurrentMenu();

	/*
	switch(selection)
	{
	case 0: menuManager->removeCurrentMenu();
			break;
	}
	*/
}