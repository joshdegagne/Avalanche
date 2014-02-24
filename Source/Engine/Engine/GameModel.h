////////////////////////////////////////////////////////////////////////////////
// Filename: GameModel.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include <d3d11.h>
#include "vertextype.h"
#include <string>
#include "IViewModel.h"

class Model;
class ColorShader;
class TextureShader;

////////////////////////////////////////////////////////////////////////////////
// Class name: GameModel
// As of 2014/02/19, this is basically identical to gamemodel from the tutorials
////////////////////////////////////////////////////////////////////////////////
class GameModel : public IViewModel
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
	//draw method with different params instead?
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);


protected:



	//Construction translate and orient matrices
    XMFLOAT4X4 orientRotateMatrix; //matrix to orient object in model co-ord system
    XMFLOAT4X4 orientTranslateMatrix; //matrix to translate object in model co-ord system
    XMFLOAT4X4 dimensionScaleMatrix; //matrix to scale object in model co-ord system

	//Construction World translate and rotate matrices
    XMFLOAT4X4 worldRotateMatrix; //matrix to orient object in model co-ord system
    XMFLOAT4X4 worldTranslateMatrix; //matrix to translate object in model co-ord system

};

