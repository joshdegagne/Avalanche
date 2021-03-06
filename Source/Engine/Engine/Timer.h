////////////////////////////////////////////////////////////////////////////////
// Filename: Timer.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ITimedObject.h"

///////////////////////////////////////////////////////////////////////////////
// Interface Name: IPlayerListener
////////////////////////////////////////////////////////////////////////////////
class Timer {
public:
	void  initialize(float, ITimedObject*);
	void  update(float);
	float getProgressPercentage();
	void  forceTimerEnd();
	bool  operator==(Timer&);
private:
	float		 initialTime; //If set to a negative value, it is an inactive timer!
	float		 time;
	ITimedObject* originalObject;
};