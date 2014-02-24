
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
 *		Returns the EntityType associated with this ViewModel.
 */
template <class T>
EntityType ViewModel<T>::GetAssociatedType()
{
	return associatedType;
}
