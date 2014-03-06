
#include "Entity.h"
#include "LogViewModel.h"
#include "PlayerViewModel.h"
#include "BoundViewModel.h"
#include "RockViewModel.h"

#include "ModelManager.h"

ModelManager::ModelManager()
{
	models = nullptr;
}

ModelManager::~ModelManager()
{
	if(models)
	{
		for(int i = 0; i < models->size(); ++i)
			if(models->elementAt(i))
				delete models->elementAt(i);

		delete models;
		models = nullptr;
	}
}

bool ModelManager::initialize(Game& game)
{

	//create the model collection
	models = new ArrayList<ViewModelBase>();
	if(!models)
		return false;

	//create all the models
	models->add(new PlayerViewModel());
	models->add(new LogViewModel());
	//models->add(new BoundViewModel());
	models->add(new RockViewModel());

	for(int i = 0; i < models->size(); ++i)
		if(models->elementAt(i) == nullptr)
			return false;


	return true;
}

void ModelManager::update(float elapsedTime)
{
	// nothing to update
}