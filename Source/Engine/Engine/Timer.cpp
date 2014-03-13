#include "Timer.h"

void Timer::initialize(float iTime, ITimedObject* object)
{
	initialTime = iTime;
	time = initialTime;
	originalObject = object;
}

void Timer::update(float elapsedTime)
{
	if (time <= 0.0f) //Inactive or finished timer duration check
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
	float t = time;
	if (t < 0.0f)
		t = 0.0f;
	return 1.0f - t/initialTime;
}