#pragma once

#include <DirectXMath.h>
#include "vertextypes.h"
#include "ModelUtil.h"
#include "Model.h"


#include <string>

using namespace DirectX;

class QuadModel : public Model
	//This model represents a quad made up of two trianges.
	//One of lengthX, lengthY, or lengthZ must be 0;
{
public:
	QuadModel(float lengthX, float lengthY, XMFLOAT4 * pColor = 0);
	virtual ~QuadModel(void);
	virtual void Shutdown();

protected:
	virtual void InitializeModel(float lengthX, float lengthY, XMFLOAT4 * pColor);

};

