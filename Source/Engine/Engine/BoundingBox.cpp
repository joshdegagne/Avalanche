#include "BoundingBox.h"

BoundingBox::BoundingBox()
{	
	parent     = 0;
	dimensions = XMFLOAT3(0.0f, 0.0f, 0.0f);
	offset     = XMFLOAT3(0.0f, 0.0f, 0.0f);
	type       = EntityType::BOUNDING_BOX;
}

BoundingBox::~BoundingBox()
{

}


void BoundingBox::initialize(Entity* e)
{
	parent = e;

	if (parent->getEntityType() == EntityType::PLAYER)
	{
		dimensions = XMFLOAT3(0.5f, 0.5f, 1.0f);
		offset     = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	else if (parent->getEntityType() == EntityType::LOG)
	{
		dimensions = XMFLOAT3(0.6f, 3.0f, 0.5f);
		offset     = XMFLOAT3(0.0f, 1.5f, 0.0f);
	}
	else if (parent->getEntityType() == EntityType::ROCK_BIG)
	{
		dimensions = XMFLOAT3(1.1f, 1.5f, 1.45f);
		offset     = XMFLOAT3(0.0f, 0.5f, 0.0f);
	}
	else
	{
		dimensions = XMFLOAT3(1.0f, 1.0f, 1.0f);
		offset     = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}


	update();
}

Entity* BoundingBox::getParent() { return parent; }

XMFLOAT3* BoundingBox::getDimensions() { return &dimensions; }

XMFLOAT3* BoundingBox::getPosition() { return &position; }

void BoundingBox::update()
{
	position.x = parent->getPosition().x + offset.x;
	position.y = parent->getPosition().y + offset.y;
	position.z = parent->getPosition().z + offset.z;
}