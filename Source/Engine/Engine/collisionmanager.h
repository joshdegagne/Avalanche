////////////////////////////////////////////////////////////////////////////////
// Filename: CollisionManager.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//#include "IManager.h"
#include "arraylist.h"
#include "DebugDefinitions.h"

class Player;
class Obstacle;
class BoundingBox;

////////////////////////////////////////////////////////////////////////////////
// Class: CollisionManager
////////////////////////////////////////////////////////////////////////////////
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	void addPlayerReference(Player&);
	void addObstacleReference(Obstacle&);
	void checkForCollisions(float);

private:
	ArrayList<Player>*	 players;
	ArrayList<Obstacle>* obstacles;

	bool intersects(BoundingBox*, BoundingBox*);



};