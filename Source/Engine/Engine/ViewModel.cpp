
#include "EntityType.h"
#include "ViewModel.h"

using namespace std;

//CONSTRUCTOR
template<class T>
inline ViewModel<T>::ViewModel(EntityType associatedType)
{
	entityList = new ArrayList<T>();

	this->associatedEntity = associatedType;

	XMStoreFloat4x4(&orientRotateMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&orientTranslateMatrix, XMMatrixIdentity());
}

//DESTRUCTOR
template<class T>
inline ViewModel<T>::~ViewModel()
{
	delete entityList;
}

/*	Add
 *	==================================================
 *		Adds the specified Entity to the list of
 *	entitys drawn by this ViewModel.
 *
 *		entity : the entity to be added
 */
template <class T>
void ViewModel<T>::Add(T* entity)
{
	entityList->add(entity);
}

/*	GetAssociatedType
 *	==================================================
 *		Returns the EntityType associated with this
 *	ViewModel.
 */
template <class T>
EntityType ViewModel<T>::GetAssociatedType()
{
	return associatedType;
}

template <class T>
XMFLOAT4X4 ViewModel<T>::GetOrientation()
{
    
	//Build the world matrix to give to the graphis system
	XMFLOAT4X4 worldMatrix; 
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4(&orientRotateMatrix) * XMLoadFloat4x4(&orientTranslateMatrix));

	return worldMatrix;
}

template <class T>
void ViewModel<T>::orientRotateX(float radianAngle)
{
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&orientRotateMatrix, XMLoadFloat4x4(&orientRotateMatrix) * XMMatrixRotationX(radianAngle));
}

template <class T>
void ViewModel<T>::orientRotateY(float radianAngle)
{
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&orientRotateMatrix, XMLoadFloat4x4(&orientRotateMatrix) * XMMatrixRotationY(radianAngle));
}

template <class T>
void ViewModel<T>::orientRotateZ(float radianAngle)
{
        // orientationMatrix *= Matrix.CreateRotationY(ry);
		XMStoreFloat4x4(&orientRotateMatrix, XMLoadFloat4x4(&orientRotateMatrix) * XMMatrixRotationZ(radianAngle));
}

template <class T>
void ViewModel<T>::orientTranslate(float deltaX, float deltaY, float deltaZ)
{
		XMStoreFloat4x4(&orientTranslateMatrix, XMLoadFloat4x4(&orientTranslateMatrix) * XMMatrixTranslation(deltaX, deltaY, deltaZ));
}

template <class T>
bool ViewModel<T>::Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader)
{
	for(int i = 0; i < entityList->size(); ++i)
	{
		T* entity = entityList->elementAt(i);
		if(!RenderEntity(deviceContext, viewMatrix, projectionMatrix, colorShader, textureShader, entity))
			return false;
	}

	return true;
}