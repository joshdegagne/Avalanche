#pragma once


#include "arraylist.h"
#include "Model.h"
#include "IViewModel.h"
#include "Texture.h"

class Model;
enum class EntityType;

template <class T>
class ViewModel : public IViewModel
{
public:
	virtual ~ViewModel();

	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice) = 0;
	virtual bool initializeTextures(ID3D11Device* d3dDevice) = 0;

	bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);
	
	void Add(T* entity);

	EntityType	GetAssociatedType();

protected:
	ViewModel(EntityType);

	virtual bool RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, T* entity) = 0;

	XMFLOAT4X4 GetOrientation();

	void orientRotateX(float);
	void orientRotateY(float);
	void orientRotateZ(float);
	void orientTranslate(float, float, float);

protected:
	ArrayList<T>*	entityList;
	
	EntityType		associatedEntity;

	XMFLOAT4X4 orientRotateMatrix;
    XMFLOAT4X4 orientTranslateMatrix;
};