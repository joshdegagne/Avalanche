///////////////////////////////////////////////////////////////////////////////
// Filename: RockObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "RockObstacle.h"
#include "EntityType.h"

RockObstacle::RockObstacle(Game& g) : Obstacle(g, 1.0f, 1.0f)
{
	type = EntityType::ROCK_BIG;

	bound->initialize(this);
	// orientation?
}