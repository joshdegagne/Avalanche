///////////////////////////////////////////////////////////////////////////////
// Filename: PauseMenu.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Menu.h"

class MenuManager;

class PauseMenu : public Menu
{
public:
	PauseMenu(MenuManager*, bool = false);
	void confirmSelection();
	int getPausedPlayer();
	void setPausedPlayer(int);
private:
	int pausedPlayer;
};