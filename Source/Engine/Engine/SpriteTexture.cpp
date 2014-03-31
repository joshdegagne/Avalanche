////////////////////////////////////////////////////////////////////////////////
// Filename: SpriteTexture.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SpriteTexture.h"
#include "DebugDefinitions.h"

SpriteTexture::SpriteTexture()
{
	index = 0;
	//frameRate = 0;
	maxFrame = 0;
}

SpriteTexture::SpriteTexture(std::vector<ID3D11ShaderResourceView*> t, float i, /*float f,*/ int m)
{
	textures = t;
	index = i;
	//frameRate = f;
	maxFrame = m;
}

SpriteTexture::SpriteTexture(const SpriteTexture& other)
{
}

SpriteTexture::~SpriteTexture()
{
}

bool SpriteTexture::Initialize(ID3D11Device*, WCHAR*)
{
	return false;
}
/*
void SpriteTexture::AddSpriteViews(std::vector<ID3D11ShaderResourceView*> textures)
{
}
*/
void SpriteTexture::Shutdown()
{
	return;
}

ID3D11ShaderResourceView* SpriteTexture::GetTexture()
{
	return textures.at((int)index);
}

void SpriteTexture::update(float elapsed)
{
	// Can change SPRITE_UPDATE_SPEED via GlobalVariableValues.txt
	index += elapsed * SPRITE_UPDATE_SPEED; 

	while (index >= maxFrame) 
	{
		index -= maxFrame;
	}

	if(index < 0)
		index = 0;
}