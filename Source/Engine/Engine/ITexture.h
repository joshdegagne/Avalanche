#ifndef ITEXTURE_H
#define ITEXTURE_H


#include <d3d11.h>

class ITexture
{
public:
	virtual ID3D11ShaderResourceView* GetTexture() = 0;
	virtual bool Initialize(ID3D11Device*, WCHAR*) = 0;
};

#endif