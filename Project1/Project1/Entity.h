#ifndef ENTITY_H
#define ENTITY_H

#include <DirectXMath.h>
#include <string>

using namespace std;
using namespace DirectX;


class Entity {
	public:
		Entity();

	private:
		XMFLOAT2 pos;

	public:
		float getX();
		float getY();
		void setX(float);
		void setY(float);

		void setPos(float, float);
};

#endif