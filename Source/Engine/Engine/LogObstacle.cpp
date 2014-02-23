///////////////////////////////////////////////////////////////////////////////
// Filename: LogObstacle.cpp
////////////////////////////////////////////////////////////////////////////////
#include "LogObstacle.h"
#include "EntityType.h"

LogObstacle::LogObstacle() : Obstacle(3.0f)
{
	type = EntityType::LOG;
	// orientation?
}

LogObstacle::LogObstacle(float l, bool p, EntityType t) : Obstacle(l, p)
{
	type = t;
}

void LogObstacle::update(float elapsed)
{

}