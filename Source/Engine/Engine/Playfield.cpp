#include "Playfield.h"
#include "DebugConsole.h"


Playfield::Playfield(Player** ps, int pNum, Game* game) : numActivePlayers(pNum)
{
	//Initialize arraylist of game models
	models = new ArrayList<GameModel>;

	keyInput = game->keyInput;

	//Creates new array of length 1-4 (Depending on how many players are playing in this game)
	//Playfield itself does not know the players' numbers, just how many there are
	activePlayers = new Player*[numActivePlayers];
	for (int i = 0; i < numActivePlayers; ++i)
	{
		activePlayers[i] = ps[i];
		models->add(activePlayers[i]->getPlayerModel());
	}

	writeLabelToConsole(L"Number of controllers connected: ", numActivePlayers);

	//Test players
	testPlayers = new Player*[NUMPLAYERS];
	for (int i = 0; i < NUMPLAYERS; i++){
		testPlayers[i] = new Player(*game, i);
		models->add(testPlayers[i]->getPlayerModel());
	}

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
}

ArrayList<GameModel>* Playfield::getGameModels()
{
	return models;
}

void Playfield::update(float elapsed) 
{
	// until modelmanager is made, move both entity and gamemodel separately (logobstable entity ignored for now)
	// need to make it so that when it reaches the top it is cleared from the game or playfield
	testLogModel->worldTranslate(-SCROLL_SPEED, 0.0f, 0.0f);

	///////////////////////////
	//KEYBOARD PLAYER TESTING//
	///////////////////////////

	//Player one testing (ARROW KEYS)
	if (keyInput->IsKeyDown(VK_LEFT))
		testPlayers[0]->moveLeft();
	if (keyInput->IsKeyDown(VK_RIGHT)) 
	    testPlayers[0]->moveRight();
	if (keyInput->IsKeyDown(VK_UP))
		testPlayers[0]->moveUp();
	if (keyInput->IsKeyDown(VK_DOWN))
		testPlayers[0]->moveDown();
	//Player two testing (WASD)
	if (keyInput->IsKeyDown(ascii_A))
		testPlayers[1]->moveLeft();
	if (keyInput->IsKeyDown(ascii_D)) 
	    testPlayers[1]->moveRight();
	if (keyInput->IsKeyDown(ascii_W))
		testPlayers[1]->moveUp();
	if (keyInput->IsKeyDown(ascii_S))
		testPlayers[1]->moveDown();
	//Player three testing (TFGH)
	if (keyInput->IsKeyDown(ascii_F))
		testPlayers[2]->moveLeft();
	if (keyInput->IsKeyDown(ascii_H)) 
	    testPlayers[2]->moveRight();
	if (keyInput->IsKeyDown(ascii_T))
		testPlayers[2]->moveUp();
	if (keyInput->IsKeyDown(ascii_G))
		testPlayers[2]->moveDown();
	//Player four testing (IJKL)
	if (keyInput->IsKeyDown(ascii_J))
		testPlayers[3]->moveLeft();
	if (keyInput->IsKeyDown(ascii_L)) 
	    testPlayers[3]->moveRight();
	if (keyInput->IsKeyDown(ascii_I))
		testPlayers[3]->moveUp();
	if (keyInput->IsKeyDown(ascii_K))
		testPlayers[3]->moveDown();
}