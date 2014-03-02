#pragma once

#include <type_traits>

#include "ModelManager.h"

template<class T>
void ModelManager::add(T* entity)
{
	for(int i = 0; i < models->size(); ++i)
	{
		const std::type_info& type = models->elementAt(i)->GetType();

		if(type == typeid(T))
		{
			((ViewModel<T>*) models->elementAt(i))->Add(entity);
		}
	}
};