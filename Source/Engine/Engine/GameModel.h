#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "vertextype.h"
#include "Model.h"
#include "ColorShader.h"
#include "TextureShader.h"

#include <string>

using namespace DirectX;

/*
GameModel class represents game objects, with geometry that can be oriented and 
positioned in the world. It provides the protocols to orient and position but
does not have any geometry. Game Model subclasses provide the actual geometry
colours and textures for the game objects
*/
//Adjust these constants for smooth motion
const float ROTATION_SPEED = 0.07f; //speed to control user rotation of objects
const float TRANSLATION_INCREMENT = 0.1f; //speed to control user moved of objects

class GameModel
{
public:
	GameModel();
	virtual ~GameModel(void);

	virtual void Shutdown();

	// Access methods
	

	//Get world matrix
	virtual XMFLOAT4X4 GetWorldMatrix();
	virtual XMFLOAT4X4 GetWorldRotateMatrix();
    
	//Transformation methods to position object
	//at relative to its model axis
	virtual void orientRotateX(float ry);
	virtual void orientRotateY(float ry);
	virtual void orientRotateZ(float ry);
	virtual void orientTranslate(float deltaX, float deltaY, float deltaZ);

	//Transformation methods to position object
	//at relative to its world axis
	virtual void worldRotateX(float ry);
	virtual void worldRotateY(float ry);
	virtual void worldRotateZ(float ry);
	virtual void worldTranslate(float deltaX, float deltaY, float deltaZ);


	//virtual ModelClass*   GetVertexModel();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool initializeTextures(ID3D11Device* device);

	virtual ID3D11ShaderResourceView* GetTexture();
	virtual ID3D11ShaderResourceView* GetTexture(int i);

	//render method
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

	// Movement
	//Transformation methods to position object
	//relative to world axis

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveUp();
	virtual void MoveDown();

	virtual void RotateLeft();
	virtual void RotateRight();


protected:



	//Construction translate and orient matrices
    XMFLOAT4X4 orientRotateMatrix; //matrix to orient object in model co-ord system
    XMFLOAT4X4 orientTranslateMatrix; //matrix to translate object in model co-ord system
    XMFLOAT4X4 dimensionScaleMatrix; //matrix to scale object in model co-ord system

	//Construction World translate and rotate matrices
    XMFLOAT4X4 worldRotateMatrix; //matrix to orient object in model co-ord system
    XMFLOAT4X4 worldTranslateMatrix; //matrix to translate object in model co-ord system

};

