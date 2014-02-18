#include "Playfield.h"
#include "DebugConsole.h"

Playfield::Playfield(Player** ps, int pNum) : numActivePlayers(pNum)
{
	//Creates new array of length 1-4 (Depending on how many players are playing in this game)
	//Playfield itself does not know the players' numbers, just how many there are
	activePlayers = new Player*[numActivePlayers];
	for (int i = 0; i < numActivePlayers; ++i)
		activePlayers[i] = ps[i];

	writeLabelToConsole(L"Number of controllers connected: ", numActivePlayers);
}

Playfield::~Playfield()
{
}