#pragma once

//Collision debugging (allows for the display of bounding boxes)
//Uncomment define to show bounding boxes (may have to rebuild)
#ifndef COLLISION_DEBUG
#define COLLISION_DEBUG
#endif

#include "ArrayList.h"
#include "IManager.h"

class Game;
class Entity;
class ViewModelBase;
class IViewModel;

class ModelManager : public IManager
{
public:
	ModelManager();
	~ModelManager();

	bool initialize(Game&);
	void update(float);

	ArrayList<IViewModel>* getGameModels() { return (ArrayList<IViewModel>*) models; }

	template<class T> void add(T& entity);
private:
	ArrayList<ViewModelBase>* models;
};

//#include "ModelManager-inl.h"