#include "Timer.h"

template<class T>
void Timer<T>::initialize(float iTime, void (T::*callback) ())
{
	initialTime = iTime;
	time = initialTime;
    callbackFunction = callback;
}

template<class T>
void Timer<T>::update(float elapsedTime)
{
	if (initialTime < 0.0f) //Inactive timer duration check
		return;

	time -= elapsedTime;
	if (time <= 0)
	{
		callbackFunction; //Calls callback function (NO IT DOES NOT NEED PARENTHESES)
		time = initialTime;
	}
}

template<class T>
float Timer<T>::getProgressPercentage()
{
	return 1.0f - time/initialTime;
}