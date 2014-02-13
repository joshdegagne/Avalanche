#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "modelclass.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class ConeModel : public GameModel
{
public:
	ConeModel(float height, float radius, int nFaces, XMFLOAT4 * pColors = 0);
	virtual ~ConeModel(void);
	virtual void Shutdown();

protected:
	virtual void InitializeModel(float height, float radius, int nFaces, XMFLOAT4 * pColors);

};

