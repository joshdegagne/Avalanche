#include "BoundingBox.h"

BoundingBox::BoundingBox()
{	
	vertexCount = 8;
	indexCount  = 24;
	vertices = new ColorVertexType[vertexCount];
	indices  = new unsigned long[indexCount];
}

BoundingBox::~BoundingBox()
{
	if(vertices)
	{
		delete[] vertices;
		vertices = 0;
	}

	if(indices)
	{
		delete[] indices;
		indices = 0;
	}
}

ColorVertexType* BoundingBox::getVertices() { return vertices; }
unsigned long* BoundingBox::getIndices() { return indices; }
int	BoundingBox::getIndexCount() { return indexCount; }
int	BoundingBox::getVertexCount() { return vertexCount; }

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

void BoundingBox::update()
{
	XMFLOAT3 origin = parent->getPosition();

	vertices[0].position = XMFLOAT3(origin.x, origin.y, origin.z);								//Top left
	vertices[1].position = XMFLOAT3(origin.x + width, origin.y, origin.z);						//Top right
	vertices[2].position = XMFLOAT3(origin.x, origin.y + height, origin.z);						//Bot left
	vertices[3].position = XMFLOAT3(origin.x + width, origin.y + height, origin.z);				//Bot right
	vertices[4].position = XMFLOAT3(origin.x, origin.y, origin.z + length);						//Top left  (back)
	vertices[5].position = XMFLOAT3(origin.x + width, origin.y, origin.z + length);				//Top right (back)
	vertices[6].position = XMFLOAT3(origin.x, origin.y + height, origin.z + length);			//Bot left  (back)
	vertices[7].position = XMFLOAT3(origin.x + width, origin.y + height, origin.z + length);	//Bot right (back)

	for (int i = 0; i < vertexCount; ++i)
		vertices[i].color = colour;
	
	
	indices[0]  = 0;
	indices[1]  = 1;
	indices[2]  = 0;
	indices[3]  = 2;
	indices[4]  = 3;
	indices[5]  = 1;
	indices[6]  = 3;
	indices[7]  = 2;
	indices[8]  = 4;
	indices[9]  = 5;
	indices[10] = 4;
	indices[11] = 6;
	indices[12] = 7;
	indices[13] = 5;
	indices[14] = 7;
	indices[15] = 6;
	indices[16] = 0;
	indices[17] = 4;
	indices[18] = 1;
	indices[19] = 5;
	indices[20] = 2;
	indices[21] = 6;
	indices[22] = 3;
	indices[23] = 7;
}