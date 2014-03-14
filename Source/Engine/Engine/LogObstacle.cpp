///////////////////////////////////////////////////////////////////////////////
// Filename: LogObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "LogObstacle.h"
#include "EntityType.h"
#include "DebugConsole.h"

LogObstacle::LogObstacle(Game& g) : Obstacle(g, 3.0f, 1.0f)
{
	type = EntityType::LOG;

	bound->initialize(this);

	writeLabelToConsole(L"Bottom of the log's bounding box: ",bound->getPosition()->z);
}