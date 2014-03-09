#pragma once

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