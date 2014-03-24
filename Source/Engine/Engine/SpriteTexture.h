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
	void AddSpriteView(ID3D11ShaderResourceView*);
	void Shutdown();

	void update(float); 
	// Modify current frame by framerate, add equals, multiply elapsed time by framerate
	// Loops with frames
	// Called in render functions?

	ID3D11ShaderResourceView* GetTexture(); // Return current frame - called when rendering the current texture; TextureManager will update index?
	// Swappable with Texture
	// Framerate getter and setter

private:
	ID3D11ShaderResourceView** textures; // Frames
	float index; // Current frame - cast to int - partial steps
	float frameRate;
	int maxFrame; 
};