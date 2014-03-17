#include "TextureManager.h"
#include "ITexture.h"
#include "Texture.h"
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

	//unique_ptr<ScratchImage> image (new ScratchImage);

	// fails atm
	//HRESULT result = LoadFromWICFile(filename, WIC_FLAGS_NONE, NULL, *image);
	//HRESULT result = LoadFromDDSFile(filename, WIC_FLAGS_NONE, NULL, image);

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

	// metadata is supported
	bool support = IsSupportedTexture(device, image.GetMetadata());
	
	//ID3D11ShaderResourceView* view;
	//CreateShaderResourceView(device, image, image->GetPixelsSize(), NULL, view);
	//CreateShaderResourceView(device, 

	// dds magic number problem
	//result = CreateDDSTextureFromMemory(device, image.GetPixels(), image.GetPixelsSize(), NULL, &view);

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

	// Attempting to work like Texture's Initialize method or ViewModel initializeTexture?
	//Texture texture = new Texture();
	// Save or load into memory from file path?
	/*    HRESULT LoadFromWICFile( _In_z_ LPCWSTR szFile, _In_ DWORD flags,
                             _Out_opt_ TexMetadata* metadata, _Out_ ScratchImage& image );*/
	//unique_ptr<ScratchImage> image (new ScratchImage);
	//__RPC_unique_pointer
	//ScratchImage* image = new ScratchImage;
	/*
	    HRESULT SaveToDDSMemory( _In_ const Image& image, _In_ DWORD flags,
                             _Out_ Blob& blob );
    HRESULT SaveToDDSMemory( _In_reads_(nimages) const Image* images, _In_ size_t nimages, _In_ const TexMetadata& metadata, _In_ DWORD flags,
                             _Out_ Blob& blob );*/
	//char blob[1000];
	//hr = SaveToWICMemory(*image, DDS_FLAGS_NONE, blob);
	//hr = SaveToWICMemory(*image, DDS_FLAGS_NONE, nullptr, nullptr);
	//hr = SaveToWICMemory(*image, WIC_FLAGS_NONE, GetWICCodec(WIC_CODEC_PNG), new Blob);
	/*
	if (FAILED(hr)) 
	{
		return NULL;
	}
	*/
	//CreateDDSTextureFromMemory(device, NULL, NULL, NULL, texture->GetTexture, NULL);
	//return &texture;
}

SpriteTexture* TextureManager::loadSpriteTexture(WCHAR* filename, float width) 
{
	//SpriteTexture* spriteTexture;
	// Set float index
	// Set float frameRate
	// set int maxFrame

	// Use CopyRectangle to get Images from a larger sheet using width value
	return NULL;
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