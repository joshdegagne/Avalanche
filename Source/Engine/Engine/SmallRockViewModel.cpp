#include "EntityType.h"
#include "SmallRockObstacle.h"
#include "SmallRockViewModel.h"
#include "TextureShader.h"
#include "Texture.h"
#include "ViewModel.cpp"
#include "DebugConsole.h"


SmallRockViewModel::SmallRockViewModel() : ViewModel<SmallRockObstacle>(EntityType::ROCK_SMALL)
{
	faceTexture = nullptr;
	vertexModel = nullptr;
}

SmallRockViewModel::~SmallRockViewModel()
{
	if(vertexModel)
	{
		delete vertexModel;
		vertexModel = 0;
	}

	if(faceTexture)
	{
		delete faceTexture;
		faceTexture = 0;
	}
}

bool SmallRockViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
{
	int   slices = 8;
	int   stacks = 8;
	float radius = 0.5f;
	
	int vertexCount = (6*slices)+(4*slices*stacks);
	int indexCount  = (2*(slices+1))+(slices*(stacks-1));

	TextureVertexType* textureVertices = new TextureVertexType[vertexCount];

	unsigned long* indices = new unsigned long[indexCount];

	//Verticies
	//textureVerticies[0].position = ;
	//textureVerticies[0].texture  = ;
	//textureVerticies[1].position = ;
	//textureVerticies[1].texture  = ;
	for (int i = 0; i < slices; ++i)
	{
		//Top fan

		//Belt
		for (int j = 0; i < stacks; ++j)
		{

		}
		//Bottom Fan

	}

	bool result = vertexModel->Initialize(d3dDevice);
		if(!result) return false;

	return result;

}  

bool SmallRockViewModel::InitializeTextures(TextureManager* texMan) 
{
	bool result;

	textureFileName = new WCHAR;
	textureFileName = L"textures/temprock1.dds";

	// Create quad texture object.
	const int NUMBER_OF_TEXTURES = 3; //one for the sides and one each for top and bottom
	faceTexture = new Texture;
	if(!faceTexture) return false;

	Texture* faceTexture = new Texture;
	faceTexture = texMan->loadTexture(textureFileName);
	if (faceTexture) return false;

	return true;
}

bool SmallRockViewModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	const int NUMBER_OF_TEXTURES = 3; //one for the sides and one each for top and bottom
	faceTexture = new Texture;
	if(!faceTexture) return false;

	faceTexture = new Texture;
	result = faceTexture->Initialize(d3dDevice, textureFileName);
	if(!result) return false;

	return true;
}

bool SmallRockViewModel::RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, SmallRockObstacle* entity){

	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT3 positionVector = entity->getPosition();
	positionVector.z +=0.2f;
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation() ) * XMMatrixTranslationFromVector( XMLoadFloat3( &positionVector )));

	const int NUMBER_OF_TEXTURES = 3; //one for the sides and one each for top and bottom

	// Put the game model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	 vertexModel->Render(deviceContext);

	 //render the game model
	 //render the game model
	 bool result = textureShader->Render(deviceContext, 
		                                  vertexModel->GetIndexCount(), 
								          worldMatrix, 
								          viewMatrix, 
								          projectionMatrix,
										  faceTexture->GetTexture() //get the texture to render
										  ); 

	 if(!result) return false;
	
	return true;

}