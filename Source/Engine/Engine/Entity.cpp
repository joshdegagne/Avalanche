#include "Entity.h"
#include "Game.h"
#include "ModelManager.h"
#include "ModelManager-inl.h"


Entity::Entity(Game& g, float x, float y)
{
	position.x = x;
	position.y = y;
	position.z = 0;

	bound = new BoundingBox();
}
Entity::~Entity()
{
	delete bound;
}

float Entity::getX() { return position.x; }
float Entity::getY() { return position.y; }
void Entity::setX(float x) { position.x = x; }
void Entity::setY(float y) { position.y = y; }

XMFLOAT3 Entity::getPosition() { return position; }

BoundingBox* Entity::getBound() { return bound; }

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

void Entity::moveBy(XMFLOAT2 direction)
{
	XMVECTOR movement = XMLoadFloat2(&direction);
	moveBy(XMVectorGetX(movement), XMVectorGetY(movement));
}