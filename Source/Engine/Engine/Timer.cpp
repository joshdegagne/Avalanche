#include "Timer.h"

void Timer::initialize(float iTime, ITimedObject* object)
{
	initialTime = iTime;
	time = initialTime;
	originalObject = object;
}

void Timer::update(float elapsedTime)
{
	if (initialTime < 0.0f) //Inactive timer duration check
		return;

	time -= elapsedTime;
	if (time <= 0)
	{
		time = 0;
		originalObject->timerCallback(); //Calls callback function (NO IT DOES NOT NEED PARENTHESES)
		//time = initialTime;
	}
}

float Timer::getProgressPercentage()
{
	return 1.0f - time/initialTime;
}