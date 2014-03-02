#pragma once

#include "ArrayList.h"
#include "IManager.h"

class Entity;
class ViewModelBase;

class ModelManager : public IManager
{
public:
	ModelManager();

	bool initialize();
	void update(float);

	template<class T> void add(T* entity);
private:
	ArrayList<ViewModelBase>* models;
};

//#include "ModelManager-inl.h"