#pragma once

#include "ArrayList.h"
#include "IManager.h"
#include "ITexture.h"
#include "Texture.h"
#include "SpriteTexture.h"
#include "DirectXTex.h"
#include "Game.h"
#include <vector>

//#define  SPRITE_UPDATE_RATE 1.0f

class Game;

using namespace DirectX;

class TextureManager : public IManager
{
public:
	TextureManager();

	bool initialize(Game&); 
	void update(float);  // For SpriteTextures

	Texture* loadTexture(WCHAR*); 
	SpriteTexture* loadSpriteTexture(WCHAR*, float); 
	void unloadTexture(ITexture*); // Makes deletion

private:
	ID3D11Device* device;
	std::vector<SpriteTexture*> spriteTextures;

	ScratchImage* loadTextureFile(WCHAR*);

};