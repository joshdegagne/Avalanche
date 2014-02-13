#include "Playfield.h"
#include "DebugConsole.h"

Playfield::Playfield(Player** ps, int pNum) : numActivePlayers(pNum)
{
	activePlayers = new Player*[numActivePlayers];
	for (int i = 0; i < numActivePlayers; ++i)
		activePlayers[i] = ps[i];
	writeNumToConsole(numActivePlayers);
}

Playfield::~Playfield()
{
}