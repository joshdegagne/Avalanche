#pragma once


#include "arraylist.h"
#include "Model.h"
#include "IViewModel.h"
#include "Texture.h"

class Model;
enum class EntityType;

template <class T>
class ViewModel : IViewModel
{
public:
	ViewModel(EntityType);
	virtual ~ViewModel();

	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice) = 0;
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader) = 0;
	virtual bool initializeTextures(ID3D11Device* d3dDevice) = 0;

	virtual ID3D11ShaderResourceView* GetTexture() = 0;

	void		Add(const T&);
	EntityType GetAssociatedType();

protected:
	XMFLOAT4X4 GetOrientation();

	void orientRotateX(float);
	void orientRotateY(float);
	void orientRotateZ(float);
	void orientTranslate(float, float, float);

protected:
	ArrayList<T>*	entityList;
	EntityType		associatedEntity;

	WCHAR*			textureFileName;
	ITexture*		texture;
	Model*			vertexModel;

	XMFLOAT4X4 orientRotateMatrix;
    XMFLOAT4X4 orientTranslateMatrix;
};