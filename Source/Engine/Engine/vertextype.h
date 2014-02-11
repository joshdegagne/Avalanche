#pragma once

#include <DirectXMath.h>

using namespace DirectX;

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