#pragma once
#include <vector>
#include <raylib.h>
#include "SlotSymbol.h"
#include "Timer.h"
#include "SlotMachineState.h"

class SlotSymbol;
class Sprite;
class Timer;

class Reel
{
public:
	Reel(Vector2 pos, std::vector<Sprite> sprites, int lenght, int reelDrawLenght, Rectangle slotMachine);
	void draw();

	void startSpin(float spinLenght, float spinSpeed);
	void spin();
	void setVisibleSymbols(Rectangle arr[]);
	void stop();
	void update();
	void setPosition(Vector2 pos) { mPos = pos; }
	Vector2 getPosition() { return mPos; };
private:
	Vector2 mPos;
	std::vector<SlotSymbol> mSlotSymbols;
	int mLenght;
	int mSpriteCount;
	int mDrawLenght;
	Rectangle mRectangle;
	Timer* mSpinTimer = nullptr;
	bool mTimerStarted = false;

	float mSpinSpeed = 0.0f;
	float mSpinLenght = 0.0f;
	float mStopPosition = 0.0f;

	SlotMachineState mState = SlotMachineState::START;

	void setStartPosition(int spriteCount);
};