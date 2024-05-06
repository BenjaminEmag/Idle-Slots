#include "Timer.h"
#include "raylib.h"

void Timer::update()
{
	if( mLifeTime > 0)
		mLifeTime -= GetFrameTime();
}

void Timer::startTimer(float lifeTime)
{
	mLifeTime = lifeTime;
}


bool Timer::isTimerDone()
{
	if (this == nullptr)
		return true;

	return mLifeTime <= 0;
}