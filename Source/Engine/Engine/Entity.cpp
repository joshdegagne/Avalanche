#include "Entity.h"

Entity::Entity(float x, float y)
{
	position.x = x;
	position.y = y;
	position.z = 0;
}

float Entity::getX() { return position.x; }
float Entity::getY() { return position.y; }
void Entity::setX(float x) { position.x = x; }
void Entity::setY(float y) { position.y = y; }

EntityType Entity::getEntityType() { return type; }

XMFLOAT3 Entity::getPosition() { return position; }

void Entity::moveTo(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Entity::moveBy(float x, float y)
{
	position.x += x;
	position.y += y;
}

void Entity::moveBy(XMFLOAT2 direction, float speed)
{
	XMVECTOR movement = XMVectorScale( XMVector2Normalize( XMLoadFloat2(&direction) ), speed);
	moveBy(XMVectorGetX(movement), XMVectorGetY(movement));
}