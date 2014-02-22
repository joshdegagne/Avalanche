#pragma once

#include "IViewModel.h"
#include <list>

class Model;

template <class T>
class ViewModel : IViewModel
{
public:
	ViewModel();
	~ViewModel();

	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice);
	virtual bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);
	void Add(const T&);

private:
	std::list<T>*	entityList;
};