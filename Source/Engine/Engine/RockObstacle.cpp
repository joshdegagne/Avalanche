///////////////////////////////////////////////////////////////////////////////
// Filename: RockObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "RockObstacle.h"
#include "EntityType.h"
#include "DebugConsole.h"

RockObstacle::RockObstacle(Game& g) : Obstacle(g, 1.0f, 1.0f)
{
	type = EntityType::ROCK_BIG;

	bound->initialize(this);

	writeLabelToConsole(L"Bottom of the rock's bounding box: ",bound->getPosition()->z);
}