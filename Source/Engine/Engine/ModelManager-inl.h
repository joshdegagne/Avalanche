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
		/*
		const std::type_info& type = models->elementAt(i)->GetType();
		const std::type_info& entityType = typeid(entity);

		if(type == entityType)
		{
			((ViewModel<T>*) models->elementAt(i))->Add(&entity);
		}
		*/
		writeTextToConsole(L"WHAT IS GOING ON I DONT EVEN");
		if (models->elementAt(i)->GetAssociatedType() == entity.getEntityType())
		{
			//writeNumToConsole((int)models->elementAt(i)->GetAssociatedType());
			((ViewModel<T>*) models->elementAt(i))->Add(&entity);
			return;
		}
	}
};