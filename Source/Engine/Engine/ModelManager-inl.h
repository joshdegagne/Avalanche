#pragma once

#include <type_traits>

#include "ModelManager.h"
#include "DebugConsole.h"


using namespace std;

template<class T>
void ModelManager::add(T& entity)
{
	for(int i = 0; i < models->size(); ++i)
	{
		if (models->elementAt(i)->GetAssociatedType() == entity.getEntityType())
		{
			((ViewModel<T>*) models->elementAt(i))->Add(&entity);
			return;
		}
	}
};