#pragma once

#include "QuadTexturedModel.h"

class PlayerModel : public QuadTexturedModel
{
public:
	PlayerModel(float lengthX, float lengthY, WCHAR* aTextureFileName); // needs to be oriented to face camera
	//virtual ~PlayerModel(void);
	//virtual void Shutdown();

	// draw/render method

protected:

};