#include "Obstacle.h"
#include "DebugConsole.h"

Obstacle::Obstacle(Game& g, float l, float h, bool p) : Entity(g), length(l), height(h), present(p) {}

float Obstacle::getLength() { return length; }
bool Obstacle::isPresent() { return present; }
void Obstacle::setPresent(bool p) { present = p; }

void Obstacle::update(float elapsedTime)
{
	position.x-= OBSTACLE_DRAG_SPEED*elapsedTime; 
}

