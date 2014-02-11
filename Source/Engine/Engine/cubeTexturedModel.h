#pragma once

#include <DirectXMath.h>
#include "vertextype.h"
#include "Texture.h"
#include "model.h"
#include "gamemodel.h"


#include <string>

using namespace DirectX;

class CubeTexturedModel : public GameModel
{
public:
	CubeTexturedModel(float lengthX, float lengthY, float lengthZ, WCHAR** pTextureFileNames);
	virtual ~CubeTexturedModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
    virtual bool initializeTextures(ID3D11Device* d3dDevice);
	virtual ID3D11ShaderResourceView* GetTexture(int i);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

protected:
	virtual void InitializeModel(float lengthX, float lengthY, float lengthZ, WCHAR** pTextureFileNames);

private:
	static const int NUMBER_OF_CUBE_FACES = 6;
	WCHAR ** m_textureFileNames;  //Array of texture file names

	//TextureVertexType* m_textureVertices;	
	//unsigned long*	m_indices;

	TextureVertexType* m_textureVerticesFront;	 //vertices of front face of cube model
	TextureVertexType* m_textureVerticesBack;    //vertices of back face of cube model	
	TextureVertexType* m_textureVerticesRight;	 //vertices of right face side of cube model
	TextureVertexType* m_textureVerticesLeft;	 //vertices of left face side of cube model
	TextureVertexType* m_textureVerticesTop;	 //vertices of top face of cube model
	TextureVertexType* m_textureVerticesBottom;	 //vertices of bottom face of cube model

	unsigned long*	m_indicesFront;   //triangle indices of front face
	unsigned long*	m_indicesBack;    //triangle indices of back face
	unsigned long*	m_indicesRight;   //triangle indices of right face
	unsigned long*	m_indicesLeft;    //triangle indices of left face
	unsigned long*	m_indicesTop;     //triangle indices of top face
	unsigned long*	m_indicesBottom;  //triangle indices of bottom face


	Texture**    m_quadTextures; //Array of  6 quad textures to map to sides of cube model
	Model** m_VertexModelArray; //Array of vertex arrays to put on graphics pipeline for rendering


};

