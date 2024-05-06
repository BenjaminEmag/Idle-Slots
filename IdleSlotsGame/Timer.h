#pragma once
class Timer
{
public:
	Timer() = default;
	void startTimer(float lifeTime);
	bool isTimerDone();
	void update();

private:
	float mLifeTime = 0.0f;
};

