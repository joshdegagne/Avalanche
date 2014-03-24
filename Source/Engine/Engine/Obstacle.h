///////////////////////////////////////////////////////////////////////////////
// Filename: Obstacle.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "DirectXHelper.h"
#include "Entity.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: Obstacle
////////////////////////////////////////////////////////////////////////////////
class Obstacle : public Entity
{
	public:
		Obstacle(Game&, float = 1.0, float = 1.0, bool = false);
		float getLength();
		bool  isPresent();
		void  setPresent(bool);
		void  update(float);
	
	protected:
		//Type of obstacle
		//Obstacle size?
		float length;
		float height;
		bool  present; // whether the obstacle is on screen and moving towards players

};