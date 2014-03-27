///////////////////////////////////////////////////////////////////////////////
// Filename: CreditsMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "CreditsMenu.h"

CreditsMenu::CreditsMenu(MenuManager* menuMan, bool activity)
{
	menuManager = menuMan;
	active = activity;
	selection = 0;
	numSelections = 0;
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