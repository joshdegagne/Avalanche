#include "CollisionManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "BoundingBox.h"

void CollisionManager::addPlayerReference(Player* p)
{
	players.add(p);
}

void CollisionManager::addObstacleReference(Obstacle* o)
{
	obstacles.add(o);
}

void CollisionManager::checkForCollisions()
{
	for (int i = 0; i < players.size(); ++i)
	{
		for (int j = 0; j < obstacles.size(); ++j)
		{
			if (intersects(players.elementAt(i)->getBound(), obstacles.elementAt(j)->getBound()))
			{
				//players.elementAt(i)->collideWithObstacle(obstacles.elementAt(j));
				return;
			}
		}

		for (int j = 0; j < players.size(); ++j)
		{
			if (intersects(players.elementAt(i)->getBound(), players.elementAt(j)->getBound()))
			{
				//players.elementAt(i)->collideWithPlayer(players.elementAt(j));
				return;
			}
		}
	}
}


bool CollisionManager::intersects(BoundingBox* boundA, BoundingBox* boundB)
{
	if (boundA == boundB)
		return false;

	XMFLOAT3 A_POS = *(boundA->getPosition());
	XMFLOAT3 A_DIM = *(boundA->getDimensions());
	XMFLOAT3 B_POS = *(boundB->getPosition());
	XMFLOAT3 B_DIM = *(boundB->getDimensions());
}