
#include "ViewModel.h"

template <class T>
ViewModel<T>::ViewModel()
{
	entityList = new list<T>();
}

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