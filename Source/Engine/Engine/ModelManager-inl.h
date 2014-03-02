#pragma once

#include <type_traits>

#include "DebugConsole.h"

#include "ModelManager.h"

using namespace std;

template<class T>
void ModelManager::add(T& entity)
{
	for(int i = 0; i < models->size(); ++i)
	{

		const std::type_info& type = models->elementAt(i)->GetType();
		const std::type_info& entityType = typeid(entity);

		if(type == entityType)
		{
			writeTextToConsole(L"Entity added to ModelManager");
			((ViewModel<T>*) models->elementAt(i))->Add(&entity);
		}
	}
};