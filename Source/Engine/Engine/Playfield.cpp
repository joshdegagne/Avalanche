#include "Playfield.h"

Playfield::Playfield()
{
}

Playfield::~Playfield()
{
}

void Playfield::Initialize(int numPlayers, ControllerInputManager* I)
{
	for (int i = 0; i < numPlayers; ++i)
	{
		players[i] = new Player(i);
	}
}