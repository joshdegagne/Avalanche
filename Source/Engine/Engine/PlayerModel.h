#pragma once

#include "QuadModel.h"

class PlayerModel : public QuadModel
{
public:
	PlayerModel(float lengthX, float lengthY, XMFLOAT4 * pColor = 0); // needs to be oriented to face camera
	virtual ~PlayerModel(void);
	virtual void Shutdown();

	// draw/render method

protected:

};