////////////////////////////////////////////////////////////////////////////////
// Filename: Entity.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "BoundingBox.h"
#include "DirectXHelper.h"
#include "EntityType.h"

class BoundingBox;
////////////////////////////////////////////////////////////////////////////////
// Class name: Entity
////////////////////////////////////////////////////////////////////////////////
class Entity {
	public:
		//Constructors
		Entity(float = 0, float = 0);
		~Entity();

	protected:
		XMFLOAT3	 position;
		EntityType	 type;
		BoundingBox* bound;

	public:
		float getX();
		float getY();
		void setX(float);
		void setY(float);

		XMFLOAT3	getPosition();
		
		BoundingBox* getBound();

		void moveTo(float, float);
		void moveBy(float, float);
		void moveBy(XMFLOAT2, float);

		EntityType getEntityType();
		
		virtual void update(float) = 0;
};