////////////////////////////////////////////////////////////////////////////////
// Filename: Texture.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Texture.h"

Texture::Texture()
{
	texture = 0;
}


Texture::Texture(const Texture& other)
{
}


Texture::~Texture()
{
}


bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	// Load the texture in.
	
	result = CreateDDSTextureFromFile(device, filename, NULL, &texture, NULL);

	if(FAILED(result))
	{
		return false;
	}

	return true;

	
	//unique_ptr<ScratchImage> image (new ScratchImage);
	//ScratchImage
	//unique_p

	//HRESULT result = LoadFromWICFile(filename, WIC_FLAGS_NONE, nullptr, *image);

}

bool Texture::Initialize(ID3D11ShaderResourceView* view) 
{
	texture = view;
	return true;
}

void Texture::Shutdown()
{
	// Release the texture resource.
	if(texture)
	{
		texture->Release();
		texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* Texture::GetTexture()
{
	return texture;
}