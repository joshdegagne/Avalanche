// TextureManager.cpp
// Loads in textures for ViewModel usage from image files for the Avalanche game project
// Given a sprite width, we can automatically create an array of sprites in a SpriteTexture 
// Uses the DirectXTex library for loading image files and copying rectangles

#include "TextureManager.h"
#include "ITexture.h"
#include "Texture.h"
#include "SpriteTexture.h"
#include <memory>
#include "Game.h"
#include "Graphics.h"
#include <vector>

TextureManager::TextureManager()
{
	device = nullptr;
}

// Assigns the manager's ID3D11Device
bool TextureManager::initialize(Game& game)
{
	device = game.getDevice();
	return true;
}

// Given an elapsed time, have each loaded SpriteTexture* update its frame index
void TextureManager::update(float elapsedTime)
{
	for(std::vector<SpriteTexture*>::size_type i = spriteTextures.size() - 1; i != (std::vector<int>::size_type) -1; i--) 
	{
		spriteTextures[i]->update(elapsedTime);
	}
}

// Private function to load in an image file for loadTexture or loadSpriteTexture
// Can be DDS, TGA, PNG, JPG
ScratchImage* TextureManager::loadTextureFile(WCHAR* filename)
{
	ScratchImage* image = new ScratchImage;

	HRESULT result;
	
	// Get the filename extension
	WCHAR ext[_MAX_EXT];
	_wsplitpath_s( filename, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT );

	if ( _wcsicmp( ext, L".dds" ) == 0 )
	{
		// DirectDraw Surface, Microsoft's image container file format
		result = LoadFromDDSFile( filename, DDS_FLAGS_NONE, NULL, *image );
	}
	else if ( _wcsicmp( ext, L".tga" ) == 0 )
	{
		result = LoadFromTGAFile( filename, NULL, *image );
	}
	else
	{
		result = LoadFromWICFile( filename, WIC_FLAGS_NONE, NULL, *image );
	}
	
	if (FAILED(result)) 
	{
		return NULL;
	}

	return image;
}

// Loads an image for use as a static Texture
Texture* TextureManager::loadTexture(WCHAR* filename)
{

	ScratchImage* image = loadTextureFile(filename);

	HRESULT result;

	// ID3D11ShaderResourceView as the "image" to render
	ID3D11ShaderResourceView*  pSRV = nullptr;

	// Create an ID3D11ShaderResourceView* out of the ScratchImage* loaded in from the external file
    result = CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), image->GetMetadata(), &pSRV );

	if (FAILED(result)) 
	{
		return NULL;
	}
	
	// Make the Texture* and set its view to this newly created one
	Texture* texture = new Texture;
	texture->Initialize(pSRV);

	return texture;
}

// Load a SpriteTexture from a spritesheet image file with a given width to separate each frame
// First prepares the spritesheet for cropping, then uses CopyRectangle to crop into a vector for the SpriteTexture*
SpriteTexture* TextureManager::loadSpriteTexture(WCHAR* filename, float spriteWidth) 
{
	HRESULT result;

	ScratchImage* DxImage = loadTextureFile(filename);

	const Image* Image_1 = DxImage->GetImages();

	TexMetadata mdata = DxImage->GetMetadata();

	int spriteSheetWidth = mdata.width;

	mdata.width = spriteWidth;

	ScratchImage CropImage;
	result = CropImage.Initialize(mdata);

	if (FAILED(result)) 
	{
		return NULL;
	}

	// Get the number of frames via the file width and the sprite width
	int numFrames = 1;
	for (numFrames; spriteWidth < spriteSheetWidth/numFrames; ++numFrames) 
	{
	}
	
	std::vector<ID3D11ShaderResourceView*> frames(numFrames);

	// Crop out each sprite to make its own ID3D11ShaderResourceView for the frames vector
	for (int i = 1; i <= numFrames; i++) 
	{
		const Image* Image_2 = CropImage.GetImages();

		Rect rect((i-1)*spriteWidth, 0, spriteWidth, mdata.height);
		
		// Use CopyRectangle to get Images from a larger sheet using width value
		result = CopyRectangle(*Image_1, rect, *Image_2, TEX_FILTER_DEFAULT, 0, 0);

		if (FAILED(result)) 
		{
			return NULL;
		}

		ID3D11ShaderResourceView*  pSRV = nullptr;

		result = CreateShaderResourceView( device, Image_2, CropImage.GetImageCount(), CropImage.GetMetadata(), &pSRV );
		
		if (FAILED(result)) 
		{
			return NULL; 
		}

		frames.at(i-1) = pSRV;
	}

	frames.shrink_to_fit();
	
	SpriteTexture* spriteTex = new SpriteTexture(frames, 0.0f, numFrames);

	spriteTextures.push_back(spriteTex);

	return spriteTex;
}

// Deletes the pointer to a given texture
void TextureManager::unloadTexture(ITexture* texture)
{
	if (texture)
	{
		texture->Shutdown();
		delete texture;
		texture = 0;
	}
}