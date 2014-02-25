////////////////////////////////////////////////////////////////////////////////
// Filename: Entity.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "EntityType.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: Entity
////////////////////////////////////////////////////////////////////////////////
class Entity {
	public:
		//Constructors
		Entity(float = 0, float = 0);

	protected:
		XMFLOAT3	position;
		EntityType	type;

	public:
		float getX();
		float getY();
		void setX(float);
		void setY(float);

		XMFLOAT3	getPosition();

		void moveTo(float, float);
		void moveBy(float, float);
		void moveBy(XMFLOAT2, float);

		EntityType getEntityType();
		
		virtual void update(float) = 0;
};