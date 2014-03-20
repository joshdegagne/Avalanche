///////////////////////////////////////////////////////////////////////////////
// Filename: RockObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SmallRockObstacle.h"
#include "EntityType.h"
#include "DebugConsole.h"

SmallRockObstacle::SmallRockObstacle(Game& g) : Obstacle(g, 1.0f, 1.0f)
{
	type = EntityType::ROCK_SMALL;

	bound->initialize(this);
}