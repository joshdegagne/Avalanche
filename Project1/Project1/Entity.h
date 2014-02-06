#ifndef ENTITY_H
#define ENTITY_H

#include "DirectXHelper.h"

class Entity {
	public:
		//Constructors
		Entity(float = 0, float = 0);

	private:
		XMFLOAT2 pos;

	public:
		float getX();
		float getY();
		void setX(float);
		void setY(float);

		void setPos(float, float);
		
		XMFLOAT2 getPos();
		virtual void update(float) = 0;
};

#endif