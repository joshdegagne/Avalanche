#include "ObstacleBag.h"
#include <random>
#include "LogObstacle.h"
#include "RockObstacle.h"

#include "DebugConsole.h"

ObstacleBag::~ObstacleBag()
{
	delete finishLine;
}

void ObstacleBag::initialize(Game* game)
{
	obstacleList.add(new LogObstacle(*game));
	obstacleList.add(new LogObstacle(*game));
	obstacleList.add(new LogObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
}

Obstacle* ObstacleBag::pullRandomObstacle()
{
	while (1)
	{
		Obstacle* selectedObst = getObstacleAlgorithm();
		if (   selectedObst->getPosition().x == DEAD_X
		    && selectedObst->getPosition().y == DEAD_Y
			&& selectedObst->getPosition().z == DEAD_Z )
		{
			return selectedObst;
		}
		writeTextToConsole(L"This obstacle no workie!");
	}
}

Obstacle* ObstacleBag::pullFinishLine() { return finishLine; }

Obstacle* ObstacleBag::getObstacleAlgorithm()
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, getNumObstacles()-1);
	
	return getObstacle(dis(gen));
}

Obstacle* ObstacleBag::getObstacle(int i) 
{ 
	return obstacleList.elementAt(i); 
}
int ObstacleBag::getNumObstacles() 
{ 
	return obstacleList.size(); 
}