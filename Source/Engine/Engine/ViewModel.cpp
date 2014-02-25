
#include "EntityType.h"
#include "ViewModel.h"

//CONSTRUCTOR
template <class T>
ViewModel<T>::ViewModel(EntityType associatedType)
{
	entityList = new list<T>();

	this->associatedType = associatedType;
}

//DESTRUCTOR
template<class T>
ViewModel<T>::~ViewModel()
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
void ViewModel<T>::Add(const T& entity)
{
	entityList->push_front(entity);
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