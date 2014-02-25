#include "Entity.h"

Entity::Entity(float x, float y)
{
	setPos(x,y);
}

float Entity::getX() { return position.x; }
float Entity::getY() { return position.y; }
void Entity::setX(float x) { position.x = x; }
void Entity::setY(float y) { position.y = y; }

EntityType Entity::getEntityType() { return type; }

XMFLOAT3 Entity::getPos() { return position; }

void Entity::setPos(float x, float y)
{
	position.x = x;
	position.y = y;
}