#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include <string>

using namespace DirectX;

class XYZaxis
{
public:
	XYZaxis();
	~XYZaxis(void);

	void Initialize();
	void Shutdown();

	ColorVertexType* GetVertices();
	unsigned long*	 GetIndices();
	int				 GetVertexCount();
	int				 GetIndexCount();

private:
	void			InitializeModel();

	ColorVertexType* vertices;
	unsigned long*	 indices;
	int				 vertexCount;
	int				 indexCount;
	XMFLOAT4		 axisColor;

};

