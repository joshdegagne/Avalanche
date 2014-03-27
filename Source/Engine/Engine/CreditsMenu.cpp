///////////////////////////////////////////////////////////////////////////////
// Filename: CreditsMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "CreditsMenu.h"
#include "MenuManager.h"

CreditsMenu::CreditsMenu(MenuManager* menuMan, bool activity)
{
	menuManager = menuMan;
	active = activity;
	selection = 0;
	numSelections = 0;
	entityType = EntityType::MENU;
}

void CreditsMenu::confirmSelection()
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