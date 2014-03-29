////////////////////////////////////////////////////////////////////////////////
// Filename: MenuManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "IManager.h"
#include "Menu.h"
#include <stack>

class MainMenu;
class PlayerSelectMenu;
class PauseMenu;
class ControlsMenu;
class CreditsMenu;

///////////////////////////////////////////////////////////////////////////////
// Class Name: MenuManager
////////////////////////////////////////////////////////////////////////////////
class MenuManager : public IManager
{
public:
	~MenuManager();

	bool initialize(Game&);
	void update(float);

	void removeCurrentMenu();
	void removeAllMenus();
	void addMainMenu();
	void addPlayerSelectMenu();
	void addPauseMenu();
	void addControlsMenu();
	void addCreditsMenu();

	void sendStartGameSignal(int);
	void sendEndGameSignal();
	void sendEndProgramSignal();
	void sendUnPauseSignal();

private:
	Game* game;

	std::stack<Menu*>	menuOrderStack;
	MainMenu*			mainMenu;
	PlayerSelectMenu*	playerSelectMenu;
	PauseMenu*			pauseMenu;
	ControlsMenu*		controlsMenu;
	CreditsMenu*		creditsMenu;

	bool UP_FLAG, DOWN_FLAG, CONFIRM_FLAG, CLOSE_FLAG;

	void addMenu(Menu*);
};