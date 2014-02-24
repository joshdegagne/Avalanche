#include "Obstacle.h"

Obstacle::Obstacle(float l) : Entity()
{
	length = l;
	present = false;
}

Obstacle::Obstacle(float l, bool p) : Entity()
{
	length = l;
	present = p;
}

float Obstacle::getLength() { return length; }
bool Obstacle::isPresent() { return present; }
void Obstacle::setPresent(bool p) { present = p; }

