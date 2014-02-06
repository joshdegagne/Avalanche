#pragma once

#include <DirectXMath.h>
#include "vertextypes.h"
#include "Graphics/Texture.h"
#include "ModelUtil.h"
#include "Model.h"


#include <string>

using namespace DirectX;

class QuadTexturedModel : public Model
	//This model represents a quad made up of two trianges.
	//One of lengthX, lengthY, or lengthZ must be 0;
{
public:
	QuadTexturedModel(float lengthX, float lengthY, WCHAR* aTextureFileName);
	virtual ~QuadTexturedModel(void);
	virtual void Shutdown();
    virtual bool initializeTextures(ID3D11Device* device);
	virtual ID3D11ShaderResourceView* GetTexture();

protected:
	virtual void InitializeModel(float lengthX, float lengthY, WCHAR* aTextureFileName);

private:
	WCHAR * m_textureFileName; 
	Texture * m_quadTexture;
};
