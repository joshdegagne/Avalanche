////////////////////////////////////////////////////////////////////////////////
// Filename: XYZaxis.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "vertextype.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class name: XYZaxis
////////////////////////////////////////////////////////////////////////////////
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

