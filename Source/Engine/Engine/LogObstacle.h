///////////////////////////////////////////////////////////////////////////////
// Filename: LogObstacle.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Obstacle.h"
#include "EntityType.h"

class LogObstacle : public Obstacle
{
public:
	LogObstacle(); // default log of size 3
	LogObstacle(float, bool, EntityType);
	
	void update(float);

private:

};