#include "TextureManager.h"
#include "ITexture.h"
#include "Texture.h"

TextureManager::TextureManager(ID3D11Device* d)
{
	device = d;
}

bool TextureManager::initialize()
{
	return true;
}

void TextureManager::update(float elapsedTime)
{

}

Texture* TextureManager::loadTexture(WCHAR* filename)
{
	// Attempting to work like Texture's Initialize method or ViewModel initializeTexture?

	//Texture texture = new Texture();
	Texture* texture = new Texture;

	// Save or load into memory from file path?

	//CreateDDSTextureFromMemory(device, NULL, NULL, NULL, texture->GetTexture(), NULL);
	
	//return &texture;
	return texture;
}

SpriteTexture* TextureManager::loadSpriteTexture(WCHAR* filename, float width) 
{
	return NULL;
}

// Deletes pointer to ITexture
void TextureManager::unloadTexture(ITexture* texture)
{
}