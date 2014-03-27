#include "Menu.h"

void Menu::scrollDown()
{
	if (selection == numSelections - 1)
		selection = 0;
	else
		selection++;
}

void Menu::scrollUp()
{
	if (selection == 0)
		selection = numSelections - 1;
	else
		selection--;
}

void Menu::setActive(bool a) { active = a; }

bool Menu::isActive() { return active; }