////////////////////////////////////////////////////////////////////////////////
// Filename: SpriteTexture.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <d3d11.h>
#include "DDSTextureLoader.h"
#include "ITexture.h"

using namespace DirectX;






////////////////////////////////////////////////////////////////////////////////
// Class name: SpriteTexture
////////////////////////////////////////////////////////////////////////////////
class SpriteTexture : public ITexture
{
public:
	SpriteTexture();
	SpriteTexture(const SpriteTexture&);
	~SpriteTexture();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();

	void update(float);

	ID3D11ShaderResourceView** GetTextures();

private:
	ID3D11ShaderResourceView** texture;
};