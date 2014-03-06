#include "TextureManager.h"
#include "ITexture.h"
#include "Texture.h"
#include <memory>


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
	// Update all active SpriteTextures?
}

Texture* TextureManager::loadTexture(WCHAR* filename)
{
	
	Texture* texture = new Texture;

	ScratchImage* image = new ScratchImage;

	//unique_ptr<ScratchImage> image (new ScratchImage);

	HRESULT result = LoadFromWICFile(filename, WIC_FLAGS_NONE, NULL, *image);

	
	if (FAILED(result)) 
	{
		return NULL;
	}
	
	//return texture;
	ID3D11ShaderResourceView* view;

	result = CreateDDSTextureFromMemory(device, image->GetPixels(), image->GetPixelsSize(), NULL, &view);

	texture->Initialize(view);

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