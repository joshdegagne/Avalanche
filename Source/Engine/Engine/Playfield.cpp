#include "Playfield.h"
#include "DebugConsole.h"

////////////////////////
#include "PlayerViewModel.h"
#include "LogViewModel.h"
////////////////////////


Playfield::Playfield(Game* game) : fieldLength(20.0f), fieldWidth(6.0f)
{
	//Initialize arraylist of game models
	models = new ArrayList<GameModel>;
	viewModels = new ArrayList<IViewModel>;

	entities = new ArrayList<Entity>();
	activePlayers = new ArrayList<Player>();
	obstacles = new ArrayList<Obstacle>();

	//Creates new array of length 1-4 (Depending on how many players are playing in this game)
	//Playfield itself does not know the players' numbers, just how many there are
	//activePlayers = new Player*[numActivePlayers];
	//for (int i = 0; i < numActivePlayers; ++i)
	//{
	//	activePlayers[i] = ps[i];
	//	//models->add(activePlayers[i]->getPlayerModel());
	//}

	LogObstacle* testLogObstacle = new LogObstacle();
	placeObstacle(testLogObstacle);

	////////////////////////////////////////////
	PlayerViewModel* playerViewModel = new PlayerViewModel();
	LogViewModel*	 logViewModel	 = new LogViewModel();
	
	viewModels->add(playerViewModel);
	viewModels->add(logViewModel);

	for (int i = 0; i < activePlayers->size(); ++i)
		playerViewModel->entityList->add(activePlayers->elementAt(i));

	logViewModel->entityList->add(testLogObstacle);
	////////////////////////////////////////////
	

	for(int i = 0; i < game->GetPlayers()->size(); ++i)
	{
		//if(game->getControllerManager()->isConnected(i))
			add(game->GetPlayers()->elementAt(i));
	}

	writeLabelToConsole(L"Number of players connected: ", activePlayers->size());

	//Ground Texture. (could have an enum and a switch statement for different levels)
	WCHAR* fieldTexture = L"textures/tempsnow2.dds";
	ground = new QuadTexturedModel (fieldLength, fieldWidth, fieldTexture);
	ground->worldTranslate(fieldLength/2, 3.0f, -0.1f);
	models->add(ground);

	



	/////////////////////////////////
	/*


	WCHAR* logTextureFiles[] = {
		L"textures/tempwoodside.dds",
		L"textures/tempwoodface.dds",
		L"textures/tempwoodside.dds"
	};

	testLogModel = new LogModel(3.0f, 0.25f, 16, logTextureFiles);
	testLogModel->worldTranslate(fieldLength, 1.5f, 0);
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

void Playfield::add(Player* player)
{
	activePlayers->add(player);
	entities->add(player);
}

ArrayList<GameModel>* Playfield::getGameModels() { return models; }
ArrayList<IViewModel>* Playfield::getViewModels() { return viewModels; }

void Playfield::update(float elapsed) 
{
	for (int i = 0; i < entities->size(); ++i){
		entities->elementAt(i)->update(elapsed);
	}
}

void Playfield::placeObstacle(Entity* entity, int lane)
{
	if (lane == -1); //Then randomize based on algorithm! :D
	else
	{
		entity->moveTo(fieldWidth*(float)lane, fieldLength);
	}
}