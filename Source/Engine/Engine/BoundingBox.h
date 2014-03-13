////////////////////////////////////////////////////////////////////////////////
// Filename: BoundingBox.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "vertextype.h"
#include "EntityBase.h"
#include "Entity.h"

class Entity;

////////////////////////////////////////////////////////////////////////////////
// Class name: BoundingBox
////////////////////////////////////////////////////////////////////////////////
class BoundingBox : public EntityBase{

	public:
		BoundingBox();
		~BoundingBox();
		void initialize(Entity*);
		void update();

		Entity*    getParent();
		XMFLOAT3*  getDimensions();
		XMFLOAT3*  getPosition();

	private:
		Entity*  parent;
		XMFLOAT3 position;
		XMFLOAT3 dimensions;
		XMFLOAT3 offset;
};