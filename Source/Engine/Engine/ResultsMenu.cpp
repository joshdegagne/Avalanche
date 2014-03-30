///////////////////////////////////////////////////////////////////////////////
// Filename: ResultsMenu.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ResultsMenu.h"
#include "MenuManager.h"
#include <vector>

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
	menuManager->addMainMenu();
	/*
	switch(selection)
	{
	case 0: menuManager->removeCurrentMenu();
			break;
	}
	*/
}


std::vector<bool> ResultsMenu::getSurvivors()
{
	return survivors;
}

void ResultsMenu::setSurvivors(std::vector<bool> s)
{
	survivors = s;
}

int ResultsMenu::getNumSurvivors()
{
	int num = 0;
	for(std::vector<bool>::size_type i = survivors.size() - 1; i != (std::vector<int>::size_type) -1; i--) 
	{
		if (survivors[i])
		{
			++num;
		}
	}
	return num;
}