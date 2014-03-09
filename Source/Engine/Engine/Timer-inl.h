#include "Timer.h"

template<class T>
void Timer<T>::initialize(float iTime, void (T::*callback)())
{
	initialTime = iTime;
	time = initialTime;
    callbackFunction = callback;
}

template<class T>
void Timer<T>::update(float elapsedTime)
{
	time -= elapsedTime;
	if (time <= 0)
	{
		callbackFunction();
	}
}

template<class T>
float Timer<T>::getProgressPercentage()
{
	return 1.0f - time/initialTime;
}