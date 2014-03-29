////////////////////////////////////////////////////////////////////////////////
// Filename: Menu.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "EntityType.h"

class MenuManager;

///////////////////////////////////////////////////////////////////////////////
// Class Name: Menu
////////////////////////////////////////////////////////////////////////////////
class Menu
{
public:
	virtual void confirmSelection() = 0;
	
	bool isActive();
	void setActive(bool);

	int  getCurrentSelection();
	void resetSelection();

	void scrollUp(); 
	void scrollDown();

	EntityType getEntityType();

protected:
	MenuManager* menuManager;
	bool		 active;
	int			 selection;
	int			 numSelections;
	EntityType	 entityType; // To align with ViewModel template system
};