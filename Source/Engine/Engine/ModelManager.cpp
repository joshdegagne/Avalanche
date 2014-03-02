
#include "Entity.h"
#include "LogViewModel.h"
#include "PlayerViewModel.h"
#include "BoundViewModel.h"

#include "ModelManager.h"

ModelManager::ModelManager()
{
	models = new ArrayList<ViewModelBase>();
}

bool ModelManager::initialize()
{
	//create the model collection
	models = new ArrayList<ViewModelBase>();
	if(!models)
		return false;

	//create all the models
	models->add(new PlayerViewModel());
	models->add(new LogViewModel());
	models->add(new BoundViewModel());

	for(int i = 0; i < models->size(); ++i)
		if(models->elementAt(i) == nullptr)
			return false;

	return true;
}

void ModelManager::update(float elapsedTime)
{
	// nothing to update
}