#include "Playfield.h"
#include "DebugConsole.h"


Playfield::Playfield(Player** ps, int pNum, Game* game) : numActivePlayers(pNum)
{
	//Initialize arraylist of game models
	models = new ArrayList<GameModel>;

	//Creates new array of length 1-4 (Depending on how many players are playing in this game)
	//Playfield itself does not know the players' numbers, just how many there are
	activePlayers = new Player*[numActivePlayers];
	for (int i = 0; i < numActivePlayers; ++i)
	{
		activePlayers[i] = ps[i];
		//models->add(activePlayers[i]->getPlayerModel());
	}

	writeLabelToConsole(L"Number of players connected: ", numActivePlayers);

	// log obstacle made to test playfield scrolling - let modelmanager handle this stuff when it's available
	obstacles = new ArrayList<Obstacle>;

	//Ground Texture. (could have an enum and a switch statement for different levels)
	WCHAR* fieldTexture = L"textures/tempsnow2.dds";
	ground = new QuadTexturedModel (18.0f,6.0f,fieldTexture);
	ground->worldTranslate(9.0f,3.0f,-0.1f);
	models->add(ground);

	WCHAR* logTextureFiles[] = {
		L"textures/tempwoodside.dds",
		L"textures/tempwoodface.dds",
		L"textures/tempwoodside.dds"
	};

	testLogModel = new LogModel(3.0f, 0.25f, 16, logTextureFiles);
	testLogModel->worldTranslate(18.0f, 1.5f, 0);
	models->add(testLogModel);

	/*
	obstacles->add(new LogObstacle()); // add test obstacle entity - game model is currently made separately in game.cpp
	*/
}

Playfield::~Playfield()
{
	for (int i = 0; i , models->size(); ++i)
	{
		delete models->elementAt(i);
	}
	delete models;
	models = 0;
}

ArrayList<GameModel>* Playfield::getGameModels()
{
	return models;
}

void Playfield::update(float elapsed) 
{
	for (int i = 0; i < numActivePlayers; ++i){
		activePlayers[i]->update(elapsed);
	}
	// until modelmanager is made, move both entity and gamemodel separately (logobstable entity ignored for now)
	// need to make it so that when it reaches the top it is cleared from the game or playfield
	testLogModel->worldTranslate(-SCROLL_SPEED, 0.0f, 0.0f);
}