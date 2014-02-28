#include "Playfield.h"
#include "DebugConsole.h"

////////////////////////
#include "PlayerViewModel.h"
#include "LogViewModel.h"
#include "ViewModel.cpp"
////////////////////////


Playfield::Playfield() : fieldLength(20.0f), fieldWidth(6.0f)
{
	entities = new ArrayList<Entity>();
	activePlayers = new ArrayList<Player>();
	obstacles = new ArrayList<Obstacle>();
	models = new ArrayList<GameModel>;
	viewModels = new ArrayList<IViewModel>;
	ground = 0;
	deathArea = 0;
}

Playfield::~Playfield()
{
	delete entities;
	delete activePlayers;

	for (int i = 0; i < obstacles->size(); ++i)
		delete obstacles->elementAt(i);
	delete obstacles;

	for (int i = 0; i < models->size(); ++i)
		delete models->elementAt(i);
	delete models;
	
	for (int i = 0; i < viewModels->size(); ++i)
		delete viewModels->elementAt(i);
	delete viewModels;

	delete ground;

	entities = 0;
	activePlayers = 0;
	obstacles = 0;
	models = 0;
	viewModels = 0;
	ground = 0;
	deathArea = 0;
}

ArrayList<GameModel>* Playfield::getGameModels() { return models; }
ArrayList<IViewModel>* Playfield::getViewModels() { return viewModels; }

void Playfield::initialize(Game* game)
{
	populateLists(game);
	populateViewModels();
	associateEntitiesAndModels();
	
	addObstacleToPlayfield(obstacles->elementAt(0));
	addObstacleToPlayfield(obstacles->elementAt(1), 3);

	writeLabelToConsole(L"Number of players connected: ", activePlayers->size());

	//Ground Texture. (could have an enum and a switch statement for different levels)
	WCHAR* fieldTexture = L"textures/tempsnow2.dds";
	ground = new QuadTexturedModel (fieldLength, fieldWidth, fieldTexture);
	ground->worldTranslate(fieldLength/2, fieldWidth/2, -0.1f);
	models->add(ground);

	XMFLOAT4 deathAreaColour = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	float DAlength = fieldLength/10.0f;
	deathArea = new QuadModel (DAlength, fieldWidth, &deathAreaColour);
	deathArea->worldTranslate(-DAlength/2, fieldWidth/2, -0.1f);
	models->add(deathArea);
}
void Playfield::update(float elapsed) 
{
	for (int i = 0; i < entities->size(); ++i)
	{
		Entity* currEntity = entities->elementAt(i);

		if (currEntity->getEntityType() == EntityType::PLAYER)
		{
			checkPlayerBounds((Player*)currEntity);
			currEntity->update(elapsed);
		}
		else
		{
			currEntity->update(elapsed);
			if (currEntity->getX() < -2.0f)
			{
				kill(currEntity);
			}
		}
	}
}

//////////////////////
//Intialization Code//
//////////////////////

//Creates obstacles and places them in the obstacles arraylist
void Playfield::populateLists(Game* game)
{
	for(int i = 0; i < game->GetPlayers()->size(); ++i)
	{
			Player* player = game->GetPlayers()->elementAt(i);
			activePlayers->add(player);
			entities->add(player);
	}
	for (int i = 0; i < 3; ++i)
	{
		obstacles->add(new LogObstacle);
	}
}
//Creates the view models and places them in the viewModels arraylist
void Playfield::populateViewModels()
{
	viewModels->add(new PlayerViewModel);
	viewModels->add(new LogViewModel);
}
//Connects entities to their view models.
void Playfield::associateEntitiesAndModels()
{
	//Technically we should be able to loop through the viewModels, but we can't right now
	PlayerViewModel* pView = (PlayerViewModel*)(viewModels->elementAt(0));
	LogViewModel*	 lView = (LogViewModel*)(viewModels->elementAt(1));

	for (int i = 0; i < activePlayers->size(); ++i)
		pView->Add(activePlayers->elementAt(i));

	for (int i = 0; i < obstacles->size(); ++i)
	{
		Obstacle* currObstacle = obstacles->elementAt(i);
		if (lView->GetAssociatedType() == currObstacle->getEntityType())
			lView->Add((LogObstacle*)currObstacle);
	}
}

/////////////////
//Obstacle Code//
/////////////////
void Playfield::addObstacleToPlayfield(Obstacle* obstacle, int lane)
{
	placeObstacle(obstacle, lane);
	entities->add(obstacle);
}

void Playfield::kill(Entity* entity)
{
	entities->remove(entity);
	entity->moveTo(10.0f, -5.0f); //Moves off to the side (should only be visible for testing)
}


//Places input obstacle at the "beginning" of the playfield. Optional: Specific lane input
void Playfield::placeObstacle(Obstacle* obstacle, int lane)
{
	if (lane == -1) //Then randomize based on algorithm! :D
		lane = 0;	//This should be the randomization call (temp value for testing)

	float laneLength = fieldWidth/6;
	obstacle->moveBy(fieldLength, (laneLength)*(lane) + (laneLength)*1.5f);
	writeTextToConsole(L"Moved log to end of lane");

}

///////////////
//Player Code//
///////////////
void Playfield::checkPlayerBounds(Player* player)
{
	XMFLOAT3 position = player->getPosition(); 

	if (position.y >= fieldWidth)
	{
		player->lockLeftMovement();
	}
	else if (position.y <= 0)
	{
		player->lockRightMovement();
	}
	if (position.x >= fieldLength)
	{
		player->lockForwardMovement();
	}
	else if (position.x <= 0)
	{
		kill(player);
	}
	
	
}