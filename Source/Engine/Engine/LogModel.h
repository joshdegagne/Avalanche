#pragma once

#include "prismTexturedModel.h"

class LogModel : public PrismTexturedModel
{
public:
	LogModel(float height, float radius, int nFaces, WCHAR** pTextureFileNames);
};