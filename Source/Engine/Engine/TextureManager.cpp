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
	//spriteTextures = nullptr;
}

bool TextureManager::initialize(Game& game)
{
	device = game.getDevice();

	return true;

}

void TextureManager::update(float elapsedTime)
{
	// Update all active SpriteTextures by their frameRates? how will framerate work? sleep? look at game stuff as reference
	//for (std::vector<SpriteTexture*>::iterator i = spriteTextures.begin(); i != spriteTextures.end(); ++i)
	//{
		// increase indices and loop if reached ends
		// elapsed time?
		//spriteTextures.at(i);
		
	//}

	for(std::vector<SpriteTexture*>::size_type i = spriteTextures.size() - 1; i != (std::vector<int>::size_type) -1; i--) 
	{
    /* std::cout << someVector[i]; ... */
		//spriteTextures[i]->update(elapsedTime * 0.00075f);
		spriteTextures[i]->update(elapsedTime);
	}
}

/*
void Obstacle::update(float elapsedTime)
{
	position.x-= ENTITY_DRAG_SPEED*elapsedTime; 
}
*/

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

	mdata.width = spriteWidth;
	//mdata.height; // height of the sprite sheet itself
	//	mdata.height

	ScratchImage CropImage;
	result = CropImage.Initialize(mdata);

	if (FAILED(result)) 
	{
		return NULL;
	}

	//int numFrames 

	int numFrames = 1;

	for (numFrames; spriteWidth < spriteSheetWidth/numFrames; ++numFrames) 
	{
	}

	
	std::vector<ID3D11ShaderResourceView*> frames(numFrames);

	for (int i = 1; i <= numFrames; i++) 
	{

		const Image* Image_2 = CropImage.GetImages();

		// shift the rect x and y - for player, move the x positively by every spritewidth (100)
		// origin (topleft) - for player with 6 frames, goes 0, 100, 200, 300, 400, 500
		//Rect rect(numFrames*spriteWidth, 0, spriteWidth, mdata.height);
		Rect rect((i-1)*spriteWidth, 0, spriteWidth, mdata.height);
		//Rect rect(i*spriteWidth, 0, spriteWidth, mdata.height);

		result = CopyRectangle(*Image_1, rect, *Image_2, TEX_FILTER_DEFAULT, 0, 0);

		if (FAILED(result)) 
		{
			return NULL; // went in here
		}

		ID3D11ShaderResourceView*  pSRV = nullptr;

		result = CreateShaderResourceView( device, Image_2, CropImage.GetImageCount(), CropImage.GetMetadata(), &pSRV ); // using correct data???
		
		if (FAILED(result)) 
		{
			return NULL; // went in here
		}

		// initialize or add to *array of psrv in spritetexture*
		
		//frames.push_back(pSRV); // weird... its putting ish at the back
		//frames.insert(pSRV);
		frames.at(i-1) = pSRV;
	}

	// sprite tex stuff

	frames.shrink_to_fit();
	
	SpriteTexture* spriteTex = new SpriteTexture(frames, 0, SPRITE_UPDATE_RATE, numFrames);

	spriteTextures.push_back(spriteTex);

	return spriteTex;

	//spriteTex->AddSpriteViews(frames);

	//spriteTex->frameRate = SPRITE_UPDATE_RATE;


	//std::vector<wchar_t> buf( cwp , cwp + (ws.size() + 1) );

	//ID3D11ShaderResourceView **frames;
	//frames = new ID3D11ShaderResourceView[numFrames];

	//const int framez = numFrames;

	//ID3D11ShaderResourceView* frames [numFrames];

	//vector<ID3D11ShaderResourceView*>

	//**double pointer to view thing, dynamic so with new and delete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	//where? man or tex? tutorial... where to delete? tex?
	// allocate memmory for frames array to dump into tex - tex will delete all that ish (call the delete fxn in texman here below)
	// 1 - allocate memory for frames array of psrvs (ptr?)
	// 2 - for every frame create psrv out of cropped imgzzz
	// 3 - after all frames made, put that psrv array as in the spritetex
	// 4 - init the other spritetex dataz like framerate, numframez, index
	// 5 - put in texman array of spritetexz for updating later
	// 6 - return the spritetex ptr


	// test?! via player only, constant thing, have the looping... ask how to loop via elapsed time
	// update somewhere by texman or spritetex... ask again
	// change playerviewmodel to do spritetexture... render thing? 
	// where to do update - ez just do in viewmodle? 
	// ask how to do framerate n updating - texman? spritetex? figure out my own solution
	// oh yeah - texman updates cuz it will have references to all the thangz!!!!! iterate thru each, update by individual frameratez







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