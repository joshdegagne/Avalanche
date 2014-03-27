////////////////////////////////////////////////////////////////////////////////
// Filename: SpriteTexture.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SpriteTexture.h"

SpriteTexture::SpriteTexture()
{
	/*
	ID3D11ShaderResourceView** textures; // Frames
	float index; // Current frame - cast to int - partial steps
	float frameRate;
	int maxFrame; 
	*/

	//textures = std::vector<ID3D11ShaderResourceView*>;
	index = 0;
	frameRate = 0;
	maxFrame = 0;
}

SpriteTexture::SpriteTexture(std::vector<ID3D11ShaderResourceView*> t, int i, float f, int m)
{
	/*
	ID3D11ShaderResourceView** textures; // Frames
	float index; // Current frame - cast to int - partial steps
	float frameRate;
	int maxFrame; 
	*/

	textures = t;
	index = i;
	frameRate = f;
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
	HRESULT result;


	return false;
}

void SpriteTexture::AddSpriteViews(std::vector<ID3D11ShaderResourceView*> textures)
{
	

}

void SpriteTexture::Shutdown()
{
	//if (textures) 
	//{
	//	delete [] textures;
	//	textures = 0;
	//}
	return;
}

ID3D11ShaderResourceView* SpriteTexture::GetTexture()
{
	// Use index for current frame
	// Return the corresponding texture (for displaying)
	//ID3D11ShaderResourceView[index];


	return textures[(int)index];
	//return textures[floor(index + .5)]; 
}

void SpriteTexture::update(float elapsed) // doesnt even use elapsed yet
{
	//if (index + frameRate * elapsed * 0.00345f > maxFrame)
	//if (index + frameRate > maxFrame)
	float speed = 0.0075f;

	index += elapsed * speed;

	while (index > maxFrame) 
	{
		index -= maxFrame;
	}

	if(index < 0)
		index = 0;


	//else
		//index += frameRate * floor(elapsed + 0.5);
		//index += frameRate * elapsed;
		
	  //index += frameRate * elapsed * 0.0033f;
		
	  
	  
	//  index += frameRate * elapsed * 0.00345f;


	  //index += floor(elapsed * 0.00345f);

	  //index += elapsed * 0.005f;
	  //index += elapsed * 0.0066f;

	
//	  index += elapsed * 0.007f;
	  //index += elapsed * 0.00725f;
	  //index += elapsed * 0.0075f;
	  //index += frameRate * elapsed * 0.0035f;//
	  //index += frameRate * elapsed * 0.00375f;//
	  //index += frameRate * elapsed * 0.0040f; // not more than this

}

/*
void Obstacle::update(float elapsedTime)
{
	position.x-= ENTITY_DRAG_SPEED*elapsedTime; 
}
*/