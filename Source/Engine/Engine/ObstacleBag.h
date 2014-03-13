////////////////////////////////////////////////////////////////////////////////
// Filename: ObstacleBag.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "arraylist.h"
#include "Obstacle.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ObstacleBag
////////////////////////////////////////////////////////////////////////////////
class ObstacleBag
{
public:
	Obstacle*	pullRandomObstacle();
	Obstacle*   pullFinishLine();

	void		addFinishLine(Obstacle*);
	void		addObstacle(Obstacle*);
	void		removeObstacle(Obstacle*);
	Obstacle*	getObstacle(int);
	int			getNumObstacles();
private:
	ArrayList<Obstacle> obstacleList;
	Obstacle*			finishLine;

	Obstacle* getObstacleAlgorithm();


};