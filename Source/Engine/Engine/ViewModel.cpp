
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


template <class T>
void ViewModel<T>::Add(const T& entity)
{
	entityList->push_front(entity);
}

template <class T>
EntityType ViewModel<T>::GetAssociatedType()
{
	return associatedType;
}
