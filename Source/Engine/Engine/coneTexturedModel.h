////////////////////////////////////////////////////////////////////////////////
// Filename: ConeTexturedModel.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "vertextype.h"
#include "Texture.h"
#include "model.h"
#include "gamemodel.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class name: ConeTexturedModel
////////////////////////////////////////////////////////////////////////////////
class ConeTexturedModel : public GameModel
{
public:
	ConeTexturedModel(float height, float radius, int nFaces, WCHAR** pTextureFileNames);
	virtual ~ConeTexturedModel(void);
	virtual void Shutdown();
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
    virtual bool initializeTextures(ID3D11Device* d3dDevice);
	virtual ID3D11ShaderResourceView* GetTexture(int i);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

protected:
	virtual void InitializeModel(float height, float radius, int nFaces, WCHAR** pTextureFileNames);

	private:
	static const int NUMBER_OF_TEXTURES = 2;
	
	WCHAR ** m_textureFileNames;  //Array of texture three file names

	TextureVertexType* m_textureVertices;	 //vertices of sides of cone
	TextureVertexType* m_topTextureVertices; //vertices of top end of cone
	TextureVertexType* m_bottomTextureVertices; //vertices of bottom end of cone

	unsigned long*	m_indices; //vertex indices of side triangles of cone
	unsigned long*	m_topIndices; //vertex indices of top triangles of cone
	unsigned long*	m_bottomIndices; //vertix indices of bottom triangles of cone

	Texture**    m_faceTextures; //Array of face textures to texture the model
	Model** m_VertexModelArray; //Array of vertex arrays to put on graphics pipeline for rendering
};

