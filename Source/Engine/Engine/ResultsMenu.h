///////////////////////////////////////////////////////////////////////////////
// Filename: ResultsMenu.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Menu.h"
#include <vector>

class MenuManager;

class ResultsMenu : public Menu
{
public:
	ResultsMenu(MenuManager* menuManager, bool active = false);
	void confirmSelection();
	std::vector<bool> getSurvivors();
	void setSurvivors(std::vector<bool>);
	int getNumSurvivors();
private:
	std::vector<bool> survivors;
};