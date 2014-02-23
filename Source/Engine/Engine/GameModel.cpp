#include "gamemodel.h"
#include "Model.h"

GameModel::GameModel()
{

	//initialize all matrices to identity matrix
	XMStoreFloat4x4(&orientRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&orientTranslateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&dimensionScaleMatrix, XMMatrixIdentity());

	XMStoreFloat4x4(&worldRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&worldTranslateMatrix, XMMatrixIdentity());

}

GameModel::~GameModel(void)
{
	Shutdown();
}





void GameModel::Shutdown()
{

}



bool GameModel::InitializeVertexModels(ID3D11Device* d3dDevice){
	//subclasses who have vertices are expected to overide this method
	return false;

}

bool GameModel::initializeTextures(ID3D11Device* device){
	//subclasses who have textures are expected to overide this method
	return false;
}
ID3D11ShaderResourceView* GameModel::GetTexture(){
	//subclasses that have textures are expected to overide this method
	return 0;
}

ID3D11ShaderResourceView* GameModel::GetTexture(int i){
	//subclasses that have textures are expected to overide this method
	return 0;
}





//ModelClass* GameModel::GetVertexModel() {return m_VertexModel; }

XMFLOAT4X4 GameModel::GetWorldMatrix(){
    
	//Build the world matrix to give to the graphis system
	XMFLOAT4X4 worldMatrix; 
	XMStoreFloat4x4(&worldMatrix, 
		XMLoadFloat4x4(&orientRotateMatrix) * 
		XMLoadFloat4x4(&orientTranslateMatrix) * 
		XMLoadFloat4x4(&worldRotateMatrix) * 
		XMLoadFloat4x4(&worldTranslateMatrix)

		);

	return worldMatrix;

}

bool GameModel::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader){
	
	//Render the model on the device context using the colorShader or textureShader as appropriate
	
	return false; //subclasses must implement this method

}


XMFLOAT4X4 GameModel::GetWorldRotateMatrix(){
	return worldRotateMatrix;
}

void GameModel::orientRotateX(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&orientRotateMatrix, XMLoadFloat4x4(&orientRotateMatrix) * XMMatrixRotationX(radianAngle));

}
void GameModel::orientRotateY(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&orientRotateMatrix, XMLoadFloat4x4(&orientRotateMatrix) * XMMatrixRotationY(radianAngle));

}
void GameModel::orientRotateZ(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&orientRotateMatrix, XMLoadFloat4x4(&orientRotateMatrix) * XMMatrixRotationZ(radianAngle));

}

void GameModel::orientTranslate(float deltaX, float deltaY, float deltaZ){
		XMStoreFloat4x4(&orientTranslateMatrix, XMLoadFloat4x4(&orientTranslateMatrix) * XMMatrixTranslation(deltaX, deltaY, deltaZ));

}

void GameModel::worldRotateX(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&worldRotateMatrix, XMLoadFloat4x4(&worldRotateMatrix) * XMMatrixRotationX(radianAngle));

}
void GameModel::worldRotateY(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&worldRotateMatrix, XMLoadFloat4x4(&worldRotateMatrix) * XMMatrixRotationY(radianAngle));

}
void GameModel::worldRotateZ(float radianAngle){
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&worldRotateMatrix, XMLoadFloat4x4(&worldRotateMatrix) * XMMatrixRotationZ(radianAngle));

}

void GameModel::worldTranslate(float deltaX, float deltaY, float deltaZ){
		XMStoreFloat4x4(&worldTranslateMatrix, XMLoadFloat4x4(&worldTranslateMatrix) * XMMatrixTranslation(deltaX, deltaY, deltaZ));

}
