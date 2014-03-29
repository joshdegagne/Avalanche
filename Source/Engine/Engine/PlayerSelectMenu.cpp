///////////////////////////////////////////////////////////////////////////////
// Filename: PlayerSelectMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "PlayerSelectMenu.h"
#include "MenuManager.h"


PlayerSelectMenu::PlayerSelectMenu(MenuManager* menuMan, bool activity)
{
	menuManager = menuMan;
	active = activity;
	selection = 0;
	numSelections = 3;
	entityType = EntityType::MENU;
}

void PlayerSelectMenu::confirmSelection()
{
	switch(selection)
	{
	case 0: menuManager->sendStartGameSignal(2); // Start Game with 2 players
			break;
	case 1: menuManager->sendStartGameSignal(3); // Start Game with 3 players
			break;
	case 2: menuManager->sendStartGameSignal(4); // Start Game with 4 players
			break;
	}
}