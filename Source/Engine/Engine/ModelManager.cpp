
#include "Game.h"
#include "Entity.h"
#include "LogViewModel.h"
#include "PlayerViewModel.h"
#include "BoundViewModel.h"
#include "RockViewModel.h"
#include "SmallRockViewModel.h"
#include "TreeViewModel.h"
#include "IcePatchViewModel.h"
#include "PlayfieldViewModel.h"
#include "FinishLineViewModel.h"
#include "BoundViewModel.h"

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
	
	models->add(new PlayerViewModel(game));
	models->add(new LogViewModel());
	models->add(new RockViewModel(game));
	models->add(new SmallRockViewModel(game));
	models->add(new TreeViewModel());
	models->add(new IcePatchViewModel());
	models->add(new PlayfieldViewModel());
	models->add(new FinishLineViewModel());


	if (COLLISION_DEBUG)
	{
		models->add(new BoundViewModel());
	}

	for(int i = 0; i < models->size(); ++i)
		if(models->elementAt(i) == nullptr)
			return false;

	bool success;
	for(int i=0; i< models->size(); i++)
	{
		//IViewModel* viewModel = models->elementAt(i);
		ViewModelBase* viewModel = models->elementAt(i);

		success = viewModel->InitializeVertexModels(game.getDevice());

		if(!success)
			return false;		

		success = viewModel->InitializeTextures(game.getTextureManager());

		
		if(!success)
			return false;

	}

	return true;
}

void ModelManager::cleanUpArrayMemory()
{
	for (int i = 0; i < models->size(); ++i)
		models->elementAt(i)->cleanUpArrayMemory();
}

void ModelManager::update(float elapsedTime)
{
	// nothing to update
}