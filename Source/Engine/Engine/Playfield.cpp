#include "Playfield.h"
#include "DebugConsole.h"

////////////////////////
#include "PlayerViewModel.h"
#include "LogViewModel.h"
#include "RockViewModel.h"
#include "ViewModel.cpp"
#include "ModelManager.h"
#include "ModelManager-inl.h"
////////////////////////


Playfield::Playfield() : fieldLength(20.0f), fieldWidth(6.0f)
{
	entities = new ArrayList<Entity>();
	activePlayers = new ArrayList<Player>();
	obstacles = new ArrayList<Obstacle>();
	models = new ArrayList<GameModel>;
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
	

	delete ground;

	entities = 0;
	activePlayers = 0;
	obstacles = 0;
	models = 0;
	ground = 0;
	deathArea = 0;
}

ArrayList<GameModel>* Playfield::getGameModels() { return models; }

void Playfield::initialize(Game* game)
{
	populateLists(game);

	for(int i = 0; i < entities->size(); ++i)
		game->getModelManager()->add(*entities->elementAt(i));
	
	addObstacleToPlayfield(obstacles->elementAt(0));	//Log
	addObstacleToPlayfield(obstacles->elementAt(3), 3); //Rock

	writeLabelToConsole(L"Number of players connected: ", activePlayers->size());

	//Ground Texture. (could have an enum and a switch statement for different levels)
	WCHAR* fieldTexture = L"textures/tempsnow2.dds";
	ground = new QuadTexturedModel (fieldLength, fieldWidth, fieldTexture);
	ground->worldTranslate(fieldLength/2, fieldWidth/2, -0.25f);
	models->add(ground);

	XMFLOAT4 deathAreaColour = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	float DAlength = fieldLength/10.0f;
	deathArea = new QuadModel (DAlength, fieldWidth, &deathAreaColour);
	deathArea->worldTranslate(-DAlength/2, fieldWidth/2, -0.25f);
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
		Obstacle* obstacle = new LogObstacle();
		obstacles->add(obstacle);
		entities->add(obstacle);
	}
	for (int i = 0; i < 3; ++i)
	{
		Obstacle* obstacle = new RockObstacle();
		obstacles->add(obstacle);
		entities->add(obstacle);
	}
}

/////////////////
//Obstacle Code//
/////////////////
void Playfield::addObstacleToPlayfield(Obstacle* obstacle, int lane)
{
	placeObstacle(obstacle, lane);
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
	obstacle->moveTo(fieldLength, (laneLength)*(lane));
	writeTextToConsole(L"Moved obstacle to end of lane");

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