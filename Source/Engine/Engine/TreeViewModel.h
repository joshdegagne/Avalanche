#pragma once

#include "ViewModel.h"
#include "TextureManager.h"

class TreeObstacle;
class ITexture;
class TextureManager;

class TreeViewModel : public ViewModel<TreeObstacle>
{
public:
	TreeViewModel();
	virtual ~TreeViewModel();
	
	bool InitializeTextures(TextureManager* texMan);
	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, TreeObstacle*);

private:
	static const int NUMBER_OF_TEXTURES = 3;
	
	WCHAR ** m_textureFileNames;  //Array of texture three file names

	TextureVertexType* m_textureVertices;	 //vertices of sides of prism
	TextureVertexType* m_topTextureVertices; //vertices of top end of prism
	TextureVertexType* m_bottomTextureVertices; //vertices of bottom end of prism

	unsigned long*	m_indices; //vertex indices of side triangles of prism
	unsigned long*	m_topIndices; //vertex indices of top triangles of prism
	unsigned long*	m_bottomIndices; //vertix indices of bottom triangles of prism

	Texture** m_faceTextures; //Array of face textures to texture the model
	Model**   m_VertexModelArray; //Array of vertex arrays to put on graphics pipeline for rendering
};