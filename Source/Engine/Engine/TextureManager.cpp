#include "TextureManager.h"
#include "ITexture.h"
#include "Texture.h"

TextureManager::TextureManager()
{
}

void TextureManager::initialize()
{

}

void TextureManager::update(float elapsedTime)
{

}

Texture* TextureManager::loadTexture(WCHAR* filename) 
{
	return NULL;
}

SpriteTexture* TextureManager::loadSpriteTexture(WCHAR* filename, float width) 
{
	return NULL;
}

void TextureManager::unloadTexture(ITexture* texture)
{
}