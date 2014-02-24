#pragma once


#include <list>
#include "IViewModel.h"

class Model;
enum class EntityType;

template <class T>
class ViewModel : IViewModel
{
public:
	ViewModel(EntityType);
	~ViewModel();

	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);
	
	void		Add(const T&);
	EntityType GetAssociatedType();

private:
	std::list<T>*	entityList;
	EntityType		associatedEntity;
};