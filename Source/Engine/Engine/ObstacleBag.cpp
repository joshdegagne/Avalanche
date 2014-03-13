#include "ObstacleBag.h"
#include <random>
#include "DebugConsole.h"

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


void ObstacleBag::addObstacle(Obstacle* o) 
{ 
	obstacleList.add(o); 
}
void ObstacleBag::removeObstacle(Obstacle* o) 
{ 
	obstacleList.remove(o); 
}
Obstacle* ObstacleBag::getObstacle(int i) 
{ 
	return obstacleList.elementAt(i); 
}
int ObstacleBag::getNumObstacles() 
{ 
	return obstacleList.size(); 
}