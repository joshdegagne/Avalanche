#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "ModelHelper.h"

#include <string>

using namespace DirectX;

//Adjust these constants for smooth motion
const float ROTATION_SPEED = 0.07f; //speed to control user rotation of objects
const float TRANSLATION_INCREMENT = 0.1f; //speed to control user moved of objects

class Model
{
public:
	Model();
	virtual ~Model(void);

	virtual void Shutdown();

	// Access methods
	
	virtual ColorVertexType* GetColorVertices();
	virtual TextureVertexType* GetTextureVertices();
	virtual unsigned long*	GetIndices();
	virtual int				GetVertexCount();
	virtual int				GetIndexCount();

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


	virtual ModelClass*   GetVertexModel();
	virtual bool isColorVertexModel();
	virtual bool isTextureVertexModel();
	virtual bool initializeTextures(ID3D11Device* device);
	virtual ID3D11ShaderResourceView* GetTexture();

	// Movement
	//Transformation methods to position object
	//relative to world axis

	virtual void			MoveLeft();
	virtual void			MoveRight();
	virtual void			MoveUp();
	virtual void			MoveDown();

	virtual void			RotateLeft();
	virtual void			RotateRight();


protected:

	//Vertices that define the geomery of this object

	ColorVertexType* m_colorVertices;
	TextureVertexType* m_textureVertices;
	unsigned long*	m_indices;
	int				m_vertexCount;
	int				m_indexCount;

	ModelClass*     m_VertexModel; //vertices to put on graphics pipeline for rendering

	//Construction translate and orient matrices
    XMFLOAT4X4 m_orientRotateMatrix; //matrix to orient object in model co-ord system
    XMFLOAT4X4 m_orientTranslateMatrix; //matrix to translate object in model co-ord system
    XMFLOAT4X4 m_dimensionScaleMatrix; //matrix to scale object in model co-ord system

	//Construction World translate and rotate matrices
    XMFLOAT4X4 m_worldRotateMatrix; //matrix to orient object in model co-ord system
    XMFLOAT4X4 m_worldTranslateMatrix; //matrix to translate object in model co-ord system

};

