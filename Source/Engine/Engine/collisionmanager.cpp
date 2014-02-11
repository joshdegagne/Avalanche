#include "collisionmanager.h"


CollisionManager::CollisionManager(void)
{
}


CollisionManager::~CollisionManager(void)
{
}

void CollisionManager::MoveIfNotColliding(Robot* a, Robot* b, void (Robot::*FuncPtr)(void))
{
	// Make a copy of the robot position before it moves
	XMFLOAT3 initialRobotPosition = a->GetPosition();

	// Move the robot
	(a->*FuncPtr)();

	// If the move caused a collision, restore the robot to its initial position
	if (AreColliding(a, b))	
	{
		a->SetPosition(initialRobotPosition);
	}
}

bool CollisionManager::AreColliding(Robot* a, Robot* b)
{
	if (a->GetBoundaryType() == "circle")
	{
		float horizontal = a->GetPosition().x - b->GetPosition().x;
		float vertical = a->GetPosition().y - b->GetPosition().y;

		float hypotenuse = sqrt((horizontal*horizontal) + (vertical*vertical));

		return hypotenuse < a->GetHeight()*2 || hypotenuse < b->GetHeight()*2;
	}
	else if (a->GetBoundaryType() == "square")
	{
		float ATopEdge = a->GetPosition().y + a->GetHeight()/2;
		float ABottomEdge = a->GetPosition().y - a->GetHeight()/2;
		float ARightEdge = a->GetPosition().x + a->GetWidth()/2;
		float ALeftEdge = a->GetPosition().x - a->GetWidth()/2;

		float BTopEdge = b->GetPosition().y + b->GetHeight()/2;
		float BBottomEdge = b->GetPosition().y - b->GetHeight()/2;
		float BRightEdge = b->GetPosition().x + b->GetWidth()/2;
		float BLeftEdge = b->GetPosition().x - b->GetWidth()/2;

		return ALeftEdge < BRightEdge && 
			ARightEdge > BLeftEdge && 
			ATopEdge > BBottomEdge && 
			ABottomEdge < BTopEdge;
	}

	return false;
}