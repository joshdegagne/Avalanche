
#include <type_traits>
#include "Entity.h"
#include "IViewModel.h"

#include "ModelManager.h"

ModelManager::ModelManager()
{
	models = new ArrayList<ViewModelBase>();
}

void ModelManager::initialize()
{

}

void ModelManager::update(float elapsedTime)
{

}

template<class T>
void ModelManager::add(T* entity)
{
	for(int i = 0; i < models->size(); ++i)
	{
		if(std::is_same<models->elementAt(i)->GetType(), T>::Value)
			((ViewModel<T>*) models->elementAt(i))->add(entity);
	}
}