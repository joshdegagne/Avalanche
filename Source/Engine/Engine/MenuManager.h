////////////////////////////////////////////////////////////////////////////////
// Filename: MenuManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "IManager.h"
#include "Menu.h"
#include <stack>
#include <vector>

class MainMenu;
class PlayerSelectMenu;
class PauseMenu;
class ResultsMenu;
class ControlsMenu;
class CreditsMenu;
class MainMenuView;
class PlayerSelectMenuView;
class ResultsMenuView;
class PauseMenuView;
class ControlsMenuView;

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
	void addPauseMenu(int);
	void addResultsMenu(std::vector<bool>);
	void addControlsMenu();
	void addCreditsMenu();

	void sendStartGameSignal(int);
	void sendEndGameSignal();
	void sendEndProgramSignal();
	void sendUnPauseSignal();

	void shutdown();

	//std::stack<Menu*> getMenuOrderStack();
	void draw(Game&);

private:
	Game* game;

	std::stack<Menu*>	menuOrderStack;

	MainMenu*			mainMenu;
	PlayerSelectMenu*	playerSelectMenu;
	PauseMenu*			pauseMenu;
	ResultsMenu*		resultsMenu;
	ControlsMenu*		controlsMenu;
	CreditsMenu*		creditsMenu;

	MainMenuView*		mainMenuView;
	PlayerSelectMenuView*	playerSelectView;
	ResultsMenuView*		resultsView;
	PauseMenuView*		pauseView;
	ControlsMenuView*		controlsView;

	int controlPlayer;
	bool UP_FLAG, DOWN_FLAG, CONFIRM_FLAG, CLOSE_FLAG;

	void addMenu(Menu*);
};