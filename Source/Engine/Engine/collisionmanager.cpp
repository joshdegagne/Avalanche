#include "CollisionManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "BoundingBox.h"

#include "DebugConsole.h"

CollisionManager::CollisionManager()
{
	players	  = new ArrayList<Player>;
	obstacles = new ArrayList<Obstacle>;
}

CollisionManager::~CollisionManager()
{
	delete players;
	delete obstacles;
}

void CollisionManager::cleanUpArrayMemory()
{
	while (players->size() > 0)
		players->removeFirst();
	while (obstacles->size() > 0)
		obstacles->removeFirst();
}

void CollisionManager::addPlayerReference(Player& p)
{
	players->add(&p);
}

void CollisionManager::addObstacleReference(Obstacle& o)
{
	obstacles->add(&o);
}

void CollisionManager::checkForCollisions(float elapsedTime)
{
	for (int i = 0; i < players->size(); ++i)
	{
		for (int j = 0; j < obstacles->size(); ++j)
		{
			if (intersects(players->elementAt(i)->getBound(), obstacles->elementAt(j)->getBound()))
			{
				#ifdef COLLISION_DEBUG
				writeTextToConsole(L"Player ", false);
				writeNumToConsole(i, false);
				writeLabelToConsole(L" has collided with Obstacle ", j);
				#endif
				players->elementAt(i)->onCollide(*(obstacles->elementAt(j)));
				continue;
			}
		}

		for (int j = 0; j < players->size(); ++j)
		{
			if (intersects(players->elementAt(i)->getBound(), players->elementAt(j)->getBound()))
			{
				#ifdef COLLISION_DEBUG
				writeTextToConsole(L"Player ", false);
				writeNumToConsole(i, false);
				writeLabelToConsole(L" has collided with Player ", j);
				#endif
				players->elementAt(i)->onCollide(*(players->elementAt(j)), elapsedTime);
				continue;
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

	if (   A_POS.x + A_DIM.x/2 > B_POS.x - B_DIM.x/2 //X axis bound check
		&& B_POS.x + B_DIM.x/2 > A_POS.x - A_DIM.x/2 //X axis bound check
		&& A_POS.y + A_DIM.y/2 > B_POS.y - B_DIM.y/2 //Y axis bound check
		&& B_POS.y + B_DIM.y/2 > A_POS.y - A_DIM.y/2 //Y axis-bound check
		&& A_POS.z + A_DIM.z/2 > B_POS.z - B_DIM.z/2 //Z axis bound check
		&& B_POS.z + B_DIM.z/2 > A_POS.z - A_DIM.z/2)//Z axis-bound check
		return true;
	else
		return false;
}