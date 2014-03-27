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

bool TextureManager::initialize(Game& game)
{
	device = game.getDevice();
	return true;
}

void TextureManager::update(float elapsedTime)
{
	for(std::vector<SpriteTexture*>::size_type i = spriteTextures.size() - 1; i != (std::vector<int>::size_type) -1; i--) 
	{
		spriteTextures[i]->update(elapsedTime);
	}
}

ScratchImage* TextureManager::loadTextureFile(WCHAR* filename)
{
	ScratchImage* image = new ScratchImage;

	HRESULT result;
	
	WCHAR ext[_MAX_EXT];
	_wsplitpath_s( filename, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT );

	if ( _wcsicmp( ext, L".dds" ) == 0 )
	{
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

Texture* TextureManager::loadTexture(WCHAR* filename)
{
	Texture* texture = new Texture;

	ScratchImage* image = loadTextureFile(filename);

	HRESULT result;
	
	WCHAR ext[_MAX_EXT];
	_wsplitpath_s( filename, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT );

	if ( _wcsicmp( ext, L".dds" ) == 0 )
	{
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

	ID3D11ShaderResourceView*  pSRV = nullptr;
    result = CreateShaderResourceView( device,
        image->GetImages(), image->GetImageCount(),
        image->GetMetadata(), &pSRV );

	if (FAILED(result)) 
	{
		return NULL;
	}
	
	texture->Initialize(pSRV);

	return texture;
}

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

	int numFrames = 1;

	for (numFrames; spriteWidth < spriteSheetWidth/numFrames; ++numFrames) 
	{
	}
	
	std::vector<ID3D11ShaderResourceView*> frames(numFrames);

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

		result = CreateShaderResourceView( device, Image_2, CropImage.GetImageCount(), CropImage.GetMetadata(), &pSRV ); // using correct data???
		
		if (FAILED(result)) 
		{
			return NULL; 
		}

		frames.at(i-1) = pSRV;
	}

	frames.shrink_to_fit();
	
	SpriteTexture* spriteTex = new SpriteTexture(frames, 0, /*1,*/ numFrames);

	spriteTextures.push_back(spriteTex);

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