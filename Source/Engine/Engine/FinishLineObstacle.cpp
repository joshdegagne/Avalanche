///////////////////////////////////////////////////////////////////////////////
// Filename: FinishLineObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FinishLineObstacle.h"
#include "EntityType.h"
#include "DebugConsole.h"

FinishLineObstacle::FinishLineObstacle(Game& g) : Obstacle(g, 6.0f, 2.0f)
{
	type = EntityType::FINISH;

	bound->initialize(this);
}