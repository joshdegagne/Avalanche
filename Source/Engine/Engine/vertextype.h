////////////////////////////////////////////////////////////////////////////////
// Filename: ColorVertexType.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ColorVertexType
////////////////////////////////////////////////////////////////////////////////
struct ColorVertexType
	{
		XMFLOAT3 position;
	    XMFLOAT4 color;
	};

struct TextureVertexType
{
	XMFLOAT3 position;
	XMFLOAT2 texture;
};