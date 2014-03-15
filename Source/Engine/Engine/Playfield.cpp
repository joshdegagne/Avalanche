#include "Playfield.h"
#include <random>
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
	obstacleBag = new ObstacleBag;
}

Playfield::~Playfield()
{
	delete entities;
	delete activePlayers;

	delete obstacleBag;

	entities = 0;
	activePlayers = 0;
	obstacleBag = 0;
}

void Playfield::initialize(Game* game)
{
	timer.initialize(GAME_LENGTH, this);
	populateLists(game);

	for(int i = 0; i < activePlayers->size(); ++i)
	{
		game->getModelManager()->add(*activePlayers->elementAt(i));
#ifdef COLLISION_DEBUG
		game->getModelManager()->add(*activePlayers->elementAt(i)->getBound());
#endif
	}
	for(int i = 0; i < obstacleBag->getNumObstacles(); ++i)
	{
		game->getModelManager()->add(*obstacleBag->getObstacle(i));
#ifdef COLLISION_DEBUG
		game->getModelManager()->add(*obstacleBag->getObstacle(i)->getBound());
#endif
	}

	addObstacleToPlayfield();
}


void Playfield::update(float elapsed) 
{
	timer.update(elapsed);
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
		currEntity->getBound()->update();
	}
}

void Playfield::timerCallback()
{
	writeTextToConsole(L"Timer has finished! WHOOOOO");
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
	obstacleBag->initialize(game);
}

/////////////////
//Obstacle Code//
/////////////////
int Playfield::getLaneAlgorithm(Obstacle* obstacle)
	{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_LANES-1);
	
	while(1)
	{
		int selectedLane = dis(gen);
		if (selectedLane <= NUM_LANES - obstacle->getLength())
			return selectedLane;
	}
}



void Playfield::addObstacleToPlayfield()
{
	Obstacle* selectedObstacle = obstacleBag->pullRandomObstacle();
	int selectedLane = getLaneAlgorithm(selectedObstacle);
	placeObstacle(selectedObstacle, selectedLane);
}

void Playfield::kill(Entity* entity)
{
	entities->remove(entity);
	entity->moveTo(DEAD_X, DEAD_Y); //Moves off to the side (should only be visible for testing)
}


//Places input obstacle at the "beginning" of the playfield. Optional: Specific lane input
void Playfield::placeObstacle(Obstacle* obstacle, int lane)
{
	if (lane == -1) //Then randomize based on algorithm! :D
		lane = 0;	//This should be the randomization call (temp value for testing)
	else if (lane >= NUM_LANES)
		lane = NUM_LANES - 1;

	float laneLength = fieldWidth/NUM_LANES;
	obstacle->moveTo(fieldLength, (laneLength)*(lane));
	entities->add(obstacle);
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