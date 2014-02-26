#include "Obstacle.h"

Obstacle::Obstacle(float l, float h, bool p) : Entity(), length(l), height(h), present(p) {}

float Obstacle::getLength() { return length; }
bool Obstacle::isPresent() { return present; }
void Obstacle::setPresent(bool p) { present = p; }

void Obstacle::update(float elapsedTime)
{
}

