#include "TextureManager.h"
#include "ITexture.h"
#include "Texture.h"
#include "SpriteTexture.h"
#include <memory>
#include "Game.h"
#include "Graphics.h"


TextureManager::TextureManager()
{
	device = nullptr;
}

bool TextureManager::initialize(Game& game)
{
	device = game.getDevice();

	return true;

}

void TextureManager::update(float elapsedTime)
{
	// Update all active SpriteTextures?
}

// add error checking with returning null tex
Texture* TextureManager::loadTexture(WCHAR* filename)
{

	
	WCHAR ext[_MAX_EXT];
	_wsplitpath_s( filename, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT );
	
	Texture* texture = new Texture;

	ScratchImage image;

	HRESULT result;

	if ( _wcsicmp( ext, L".dds" ) == 0 )
	{
		result = LoadFromDDSFile( filename, DDS_FLAGS_NONE, NULL, image );
	}
	else if ( _wcsicmp( ext, L".tga" ) == 0 )
	{
		result = LoadFromTGAFile( filename, NULL, image );
	}
	else
	{
		result = LoadFromWICFile( filename, WIC_FLAGS_NONE, NULL, image );
	}
	
	if (FAILED(result)) 
	{
		return NULL;
	}

	ID3D11ShaderResourceView*  pSRV = nullptr;
    result = CreateShaderResourceView( device,
        image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &pSRV );

	// hunch: doesn't work since it's not a dds in memory?
	//result = CreateDDSTextureFromMemory(device, image.GetPixels(), image.GetPixelsSize(), NULL, &pSRV);

	if (FAILED(result)) 
	{
		return NULL;
	}
	
	texture->Initialize(pSRV);

	return texture;
	



	/*
	Texture* texture = new Texture;
	HRESULT result;
	ScratchImage DxImage;

	WCHAR ext[_MAX_EXT];
	_wsplitpath_s( filename, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT );

	if ( _wcsicmp( ext, L".dds" ) == 0 )
	{
		result = LoadFromDDSFile( filename, DDS_FLAGS_NONE, NULL, DxImage );
	}
	else if ( _wcsicmp( ext, L".tga" ) == 0 )
	{
		result = LoadFromTGAFile( filename, NULL, DxImage );
	}
	else
	{
		result = LoadFromWICFile( filename, WIC_FLAGS_NONE, NULL, DxImage );
	}
	
	if (FAILED(result)) 
	{
		return NULL;
	}


	const Image* Image_1 = DxImage.GetImages();

	TexMetadata mdata = DxImage.GetMetadata();
	mdata.width /= 2;
	mdata.height /= 2; // height of the sprite sheet itself
	//	mdata.height

	ScratchImage CropImage;
	result = CropImage.Initialize(mdata);

	if (FAILED(result)) 
	{
		return NULL;
	}

	const Image* Image_2 = CropImage.GetImages();

	Rect rect(0, 0, mdata.width, mdata.height);

	result = CopyRectangle(*Image_1, rect, *Image_2, TEX_FILTER_DEFAULT, 0, 0);

	if (FAILED(result)) 
	{
		return NULL;
	}

	ID3D11ShaderResourceView*  pSRV = nullptr;

    result = CreateShaderResourceView( device,
		Image_2, CropImage.GetImageCount(),
		CropImage.GetMetadata(), &pSRV );

	texture->Initialize(pSRV);

	return texture;
	*/
}

SpriteTexture* TextureManager::loadSpriteTexture(WCHAR* filename, float spriteWidth) 
{
	//SpriteTexture* spriteTexture;
	// Set float index to be 0?
	// Set float frameRate to be something...
	// set int maxFrame... how to decide?

	// Use CopyRectangle to get Images from a larger sheet using width value

	SpriteTexture* spriteTex = new SpriteTexture;

	HRESULT result;
	ScratchImage DxImage;

	WCHAR ext[_MAX_EXT];
	_wsplitpath_s( filename, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT );

	if ( _wcsicmp( ext, L".dds" ) == 0 )
	{
		result = LoadFromDDSFile( filename, DDS_FLAGS_NONE, NULL, DxImage );
	}
	else if ( _wcsicmp( ext, L".tga" ) == 0 )
	{
		result = LoadFromTGAFile( filename, NULL, DxImage );
	}
	else
	{
		result = LoadFromWICFile( filename, WIC_FLAGS_NONE, NULL, DxImage );
	}
	
	if (FAILED(result)) 
	{
		return NULL;
	}


	const Image* Image_1 = DxImage.GetImages();

	TexMetadata mdata = DxImage.GetMetadata();

	int spriteSheetWidth = mdata.width;

	//mdata.width = spriteWidth;
	mdata.height; // height of the sprite sheet itself
	//	mdata.height

	ScratchImage CropImage;
	result = CropImage.Initialize(mdata);

	if (FAILED(result)) 
	{
		return NULL;
	}

	//int numFrames 

	int numFrames = 1;

	for (numFrames; spriteWidth == spriteSheetWidth/numFrames; numFrames++) 
	{
	}

	//const int framez = numFrames;

	//ID3D11ShaderResourceView* frames [numFrames];

	//vector<ID3D11ShaderResourceView*>

	//**double pointer to view thing, dynamic so with new and delete



	for (numFrames; spriteWidth == spriteSheetWidth/numFrames; numFrames++) 
	{

		const Image* Image_2 = CropImage.GetImages();

		// shift the rect x and y - for player, move the x positively by every spritewidth (100)
		// origin (topleft) - for player with 6 frames, goes 0, 100, 200, 300, 400, 500
		Rect rect(numFrames*spriteWidth, 0, spriteWidth, mdata.height);

		result = CopyRectangle(*Image_1, rect, *Image_2, TEX_FILTER_DEFAULT, 0, 0);

		if (FAILED(result)) 
		{
			return NULL;
		}

		ID3D11ShaderResourceView*  pSRV = nullptr;

		result = CreateShaderResourceView( device, Image_2, CropImage.GetImageCount(), CropImage.GetMetadata(), &pSRV );



		// initialize or add to *array of psrv in spritetexture*

	}



	//DxImage.GetImages();

		//CaptureTexture(device,

	//Rect rect(0, 0, width, width);
	//DxImage.Initialize2D

	//result = CopyRectangle(NULL, NULL, NULL, TEX_FILTER_DEFAULT, 0, 0);



	// set other spritetexture members

	return spriteTex;
}

// Deletes pointer to ITexture
void TextureManager::unloadTexture(ITexture* texture)
{
	if (texture)
	{
		texture->Shutdown();
		delete texture;
		texture = 0;
	}
}