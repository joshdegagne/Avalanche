///////////////////////////////////////////////////////////////////////////////
// Filename: ResultsMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ResultsMenu.h"
#include "MenuManager.h"


ResultsMenu::ResultsMenu(MenuManager* menuMan, bool activity)
{
	menuManager = menuMan;
	active = activity;
	selection = 0;
	numSelections = 0;
	entityType = EntityType::MENU;
}

void ResultsMenu::confirmSelection()
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