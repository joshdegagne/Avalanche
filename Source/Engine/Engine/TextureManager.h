// TextureManager.h

#pragma once

#include "ArrayList.h"
#include "IManager.h"
#include "ITexture.h"
#include "Texture.h"
#include "SpriteTexture.h"
#include "DirectXTex.h"
#include "Game.h"
#include <vector>

class Game;

using namespace DirectX;

class TextureManager : public IManager
{
public:
	TextureManager();

	bool initialize(Game&); // Inherited from IManager
	void update(float);  // Inherited from IManager; here for SpriteTextures

	Texture* loadTexture(WCHAR*); 
	SpriteTexture* loadSpriteTexture(WCHAR*, float); // Takes in width of spritesheet cell
	void unloadTexture(ITexture*); // Makes deletion

private:
	ID3D11Device* device;
	std::vector<SpriteTexture*> spriteTextures; // For updating each loaded SpriteTexture* (they'll update their own indices)
	ScratchImage* loadTextureFile(WCHAR*); // Loads a ScratchImage* from a DDS, PNG, other other WIC file
};