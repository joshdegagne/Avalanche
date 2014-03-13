////////////////////////////////////////////////////////////////////////////////
// Filename: Entity.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "BoundingBox.h"
#include "DirectXHelper.h"
#include "EntityBase.h"

#define DEAD_X 10.0f
#define DEAD_Y -5.0f
#define DEAD_Z 0.0f

class Game;

class BoundingBox;
////////////////////////////////////////////////////////////////////////////////
// Class name: Entity
////////////////////////////////////////////////////////////////////////////////
class Entity : public EntityBase {
	public:
		//Constructors
		Entity(Game&, float = DEAD_X, float = DEAD_Y);
		~Entity();

	protected:
		XMFLOAT3	 position;
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
		
		virtual void update(float) = 0;
};