////////////////////////////////////////////////////////////////////////////////
// Filename: SpriteTexture.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <d3d11.h>
#include "DDSTextureLoader.h"
#include "ITexture.h"
#include <vector>

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: SpriteTexture
////////////////////////////////////////////////////////////////////////////////
class SpriteTexture : public ITexture
{
public:
	SpriteTexture();
	SpriteTexture(std::vector<ID3D11ShaderResourceView*>, int, /*float,*/ int);
	SpriteTexture(const SpriteTexture&);
	~SpriteTexture();

	bool Initialize(ID3D11Device*, WCHAR*);
	//void AddSpriteViews(std::vector<ID3D11ShaderResourceView*>);
	void Shutdown();

	void update(float); 

	ID3D11ShaderResourceView* GetTexture(); // Return current frame - called when rendering the current texture

private:
	std::vector<ID3D11ShaderResourceView*> textures;
	float index; // Current frame - cast to int
	//float frameRate; // Unused?
	int maxFrame; 
};