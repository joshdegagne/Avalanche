#include "Menu.h"
#include "MenuManager.h"

bool Menu::isActive() { return active; }
void Menu::setActive(bool a) { active = a; }
int  Menu::getCurrentSelection() { return selection; }
void Menu::resetSelection() { selection = 0; }

void Menu::scrollUp()
{
	if (selection == 0)
		selection = numSelections - 1;
	else
		selection--;
}

void Menu::scrollDown()
{
	if (selection == numSelections - 1)
		selection = 0;
	else
		selection++;
}

