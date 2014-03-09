#include "Timer.h"

void Timer::initialize(float iTime, void (*callback)())
{
	initialTime = iTime;
	time = initialTime;
    callbackFunction = callback;
}

void Timer::update(float elapsedTime)
{
	time -= elapsedTime;
	if (time <= 0)
	{
		callbackFunction();
	}
}

float Timer::getProgressPercentage()
{
	return 1.0f - time/initialTime;
}