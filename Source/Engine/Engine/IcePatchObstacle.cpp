///////////////////////////////////////////////////////////////////////////////
// Filename: IcePatchObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "IcePatchObstacle.h"
#include "EntityType.h"
#include "DebugConsole.h"

IcePatchObstacle::IcePatchObstacle(Game& g) : Obstacle(g, 6.0f, 0.1f)
{
	type = EntityType::ICE_PATCH;

	bound->initialize(this);
}