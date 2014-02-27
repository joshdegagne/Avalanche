////////////////////////////////////////////////////////////////////////////////
// Filename: BoundingBox.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "vertextype.h"
#include "Entity.h"

class Entity;
////////////////////////////////////////////////////////////////////////////////
// Class name: BoundingBox
////////////////////////////////////////////////////////////////////////////////
class BoundingBox {

	public:
		BoundingBox();
		~BoundingBox();
		void initialize(Entity*);
		void update();

		ColorVertexType* getVertices();
		unsigned long*	 getIndices();
		int				 getIndexCount();
		int				 getVertexCount();


	private:
		void setWLH(float, float, float);

		Entity* parent;
		float   width;
		float   length;
		float   height;
		ColorVertexType* vertices;
		unsigned long*	 indices;
		int				 vertexCount;
		int				 indexCount;
		XMFLOAT4		 colour;

};