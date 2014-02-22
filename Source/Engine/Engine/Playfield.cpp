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


	// log obstacle made to test playfield scrolling - let modelmanager handle this stuff when it's available
	obstacles = new ArrayList<Obstacle>;

	WCHAR* logTextureFiles[] = {
		L"textures/tempwoodside.dds",
		L"textures/tempwoodface.dds",
		L"textures/tempwoodside.dds"
	};

	testLogModel = new LogModel(3.0f, 0.25f, 16, logTextureFiles);

	/*
	obstacles->add(new LogObstacle()); // add test obstacle entity - game model is currently made separately in game.cpp
	*/
}

Playfield::~Playfield()
{
}

void Playfield::update(float elapsed) 
{
	// until modelmanager is made, move both entity and gamemodel separately (logobstable entity ignored for now)
	// need to make it so that when it reaches the top it is cleared from the game or playfield
	testLogModel->worldTranslate(-SCROLL_SPEED, 0.0f, 0.0f);

}

LogModel* Playfield::getTestLogModel() { return testLogModel; }