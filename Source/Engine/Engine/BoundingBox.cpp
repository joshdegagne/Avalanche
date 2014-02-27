#include "BoundingBox.h"

BoundingBox::BoundingBox()
{	

}

BoundingBox::~BoundingBox()
{

}


void BoundingBox::initialize(Entity* e)
{
	parent = e;

	if (parent->getEntityType() == EntityType::PLAYER)
		setWLH(1.0f, 1.0f, 1.0f);
	else if (parent->getEntityType() == EntityType::LOG)
		setWLH(3.0f, 1.0f, 1.0f);
	else
		setWLH(1.0f, 1.0f, 1.0f);

	update();
}

void BoundingBox::setWLH(float w, float l, float h)
{
	width  = w;
	length = l;
	height = h;
}

Entity* BoundingBox::getParent() { return parent; }

XMFLOAT3* BoundingBox::getDimensions()
{
	XMFLOAT3* result = new XMFLOAT3(length,width,height);
	return result;
}

void BoundingBox::update()
{
	XMFLOAT3 origin = parent->getPosition();


}