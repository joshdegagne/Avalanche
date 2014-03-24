#include "EntityType.h"
#include "RockObstacle.h"
#include "RockViewModel.h"
#include "TextureShader.h"
#include "Texture.h"
#include "ViewModel.cpp"
#include "DebugConsole.h"

RockViewModel::RockViewModel(Game& game) : ViewModel<RockObstacle>(EntityType::ROCK_BIG)
{
	context = game.getContext();
	blendState = game.getBlendState();
    }

RockViewModel::~RockViewModel()
{
	if(faceTexture)
	{
		delete faceTexture;
		faceTexture = 0;
	}
	}

bool RockViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
	{
	textureFileName = new WCHAR;
	textureFileName = L"textures/temprock1.dds";
	sphere = GeometricPrimitive::CreateSphere(context, 2.0f, 4, false);
	if (!sphere) return false;

	return true;
	}

bool RockViewModel::InitializeTextures(TextureManager* texMan) 
{
	//bool result;

	// Create quad texture object.
	faceTexture = new Texture;
	if(!faceTexture) return false;

	Texture* faceTexture = new Texture;
	faceTexture = texMan->loadTexture(textureFileName);
	if (!faceTexture) return false;

	return true;
}

bool RockViewModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	faceTexture = new Texture;
	if(!faceTexture) return false;

	faceTexture = new Texture;
	result = faceTexture->Initialize(d3dDevice, textureFileName);
	if(!result) return false;

	return true;
}

bool RockViewModel::RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, RockObstacle* entity){

	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT3 positionVector = entity->getPosition();
	positionVector.z +=0.2f;
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation() ) * XMMatrixTranslationFromVector( XMLoadFloat3( &positionVector )));

	 //render the game model
	sphere->Draw(XMLoadFloat4x4(&worldMatrix),XMLoadFloat4x4(&viewMatrix),XMLoadFloat4x4(&projectionMatrix),Colors::DarkSlateGray,faceTexture->GetTexture(), false, [=]
	{
		context->OMSetBlendState( blendState, nullptr, 0xFFFFFFFF);
	});

	if(!sphere) return false;
	
	return true;
}