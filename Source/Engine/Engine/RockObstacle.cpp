///////////////////////////////////////////////////////////////////////////////
// Filename: RockObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "RockObstacle.h"
#include "EntityType.h"
#include "DebugConsole.h"

RockObstacle::RockObstacle(Game& g) : Obstacle(g, 2.0f, 2.0f)
{
	type = EntityType::ROCK_BIG;

	bound->initialize(this);
}