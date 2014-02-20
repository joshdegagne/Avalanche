#include "Obstacle.h"

Obstacle::Obstacle(float l) : Entity()
{
	length = l;
}

float Obstacle::getLength() { return length; }