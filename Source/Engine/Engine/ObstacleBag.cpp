#include "ObstacleBag.h"
#include <random>
#include "LogObstacle.h"
#include "RockObstacle.h"
#include "FinishLineObstacle.h"

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
	obstacleList.add(new LogObstacle(*game));
	obstacleList.add(new LogObstacle(*game));
	obstacleList.add(new LogObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	obstacleList.add(new RockObstacle(*game));
	
	finishLine = new FinishLineObstacle(*game);
}

Obstacle* ObstacleBag::pullRandomObstacle()
{
	for (int i = 0; i < 100; ++i) 
	{
		Obstacle* selectedObst = getObstacleAlgorithm();
		if (   selectedObst->getPosition().x == DEAD_X
		    && selectedObst->getPosition().y == DEAD_Y
			&& selectedObst->getPosition().z == DEAD_Z )
		{
			return selectedObst;
		}
	}
	
	return nullptr;
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