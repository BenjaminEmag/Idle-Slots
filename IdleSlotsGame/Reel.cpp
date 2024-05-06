#include "Reel.h"
#include "Sprite.h"
#include <raylib.h>
#include "SlotSymbol.h"
#include <iostream>
#include <cstdlib>

Reel::Reel(Vector2 pos, std::vector<Sprite> sprites, int lenght, int reelDrawLenght, Rectangle slotMachine) : mPos(pos), mLenght(lenght), mDrawLenght(reelDrawLenght), mRectangle(slotMachine)
{
	mSpriteCount = sprites.size();

	Vector2 spritePos{ mPos.x, mPos.y + (lenght - 1) * sprites[0].getHeight() };

	for (int i = 0; i < mDrawLenght; i++)
	{
		int iter = i % sprites.size(); // loops through list

		mSlotSymbols.push_back(SlotSymbol(sprites[iter]));
		mSlotSymbols[i].setPosition(spritePos);
		spritePos.y = spritePos.y - sprites[iter].getHeight();
	}
	mStopPosition = mSlotSymbols[0].getPosition().y;
}

void Reel::setStartPosition(int spriteCount)
{
	Vector2 spritePos{ mPos.x, mPos.y + (mLenght - 1) * mSlotSymbols[0].getHeight() };

	for (int i = 0; i < mDrawLenght; i++)
	{
		int iter = i % spriteCount; // loops through list

		mSlotSymbols[i].setPosition(spritePos);
		spritePos.y = spritePos.y - mSlotSymbols[0].getHeight();
	}
	mStopPosition = mSlotSymbols[0].getPosition().y;
}
void Reel::draw()
{
	for (int i = 0; i < mDrawLenght; i++)
	{
		int iter = i % mSlotSymbols.size(); // loops through list

		mSlotSymbols[iter].draw();
	}
}

void Reel::update()
{
	if (mSpinTimer != nullptr)
		mSpinTimer->update();

	switch (mState)
	{
	case SlotMachineState::START:
		break;
	case SlotMachineState::SPIN:
		spin();
		break;
	case SlotMachineState::STOP:
		stop();
		break;
	default:
		break;
	}

	for (int i = 0; i < mDrawLenght; i++)
	{
		//mSlotSymbols[i].setPosition(mSpriteLocation[i]);
		mSlotSymbols[i].update();
	}
}

void Reel::startSpin(float spinLenght, float spinSpeed)
{
	if (mTimerStarted == false)
	{
		mSpinTimer = new Timer();
		mSpinTimer->startTimer(spinLenght);
		mTimerStarted = true;
	}
	mSpinSpeed = spinSpeed;
	mState = SlotMachineState::SPIN;
}

void Reel::spin()
{
	if (mState != SlotMachineState::SPIN)
		return;

	if (mSpinTimer->isTimerDone())
	{
		delete mSpinTimer;
		mSpinTimer = nullptr;
		mTimerStarted = false;

		mState = SlotMachineState::STOP;
	}

	for (int i = 0; i < mDrawLenght; i++)
	{
		int iter = i % mSlotSymbols.size();
		mSlotSymbols[i].setPosition(Vector2{ mSlotSymbols[i].getPosition().x, mSlotSymbols[i].getPosition().y + mSpinSpeed });


		if (mSlotSymbols[i].getPosition().y > mRectangle.y + mRectangle.height)
			mSlotSymbols[i].setPosition(Vector2{ mSlotSymbols[i].getPosition().x, mRectangle.y - (mDrawLenght - mLenght) * mSlotSymbols[i].getHeight() });
	}
}

void Reel::setVisibleSymbols(Rectangle rects[])
{
	for (int i = 0; i < mLenght; i++)
	{
		mSlotSymbols[i].setSlotSymbol(rects[i]);
	}
}

void Reel::stop()
{
	if (mState != SlotMachineState::STOP)
		return;

	float buffer = mSpinSpeed / 2.0;

	if (mSlotSymbols[0].getPosition().y >= (mStopPosition - buffer) && mSlotSymbols[0].getPosition().y <= (mStopPosition + buffer))
	{
		mSlotSymbols[0].setPosition(Vector2{ mSlotSymbols[0].getPosition().x, mStopPosition });
		setStartPosition(mSpriteCount);

		mState = SlotMachineState::START;
		return;
	}

	for (int i = 0; i < mDrawLenght; i++)
	{
		int iter = i % mSlotSymbols.size();
		mSlotSymbols[i].setPosition(Vector2{ mSlotSymbols[i].getPosition().x, mSlotSymbols[i].getPosition().y + (buffer / 2) });

		if (mSlotSymbols[i].getPosition().y > mRectangle.y + mRectangle.height)
			mSlotSymbols[i].setPosition(Vector2{ mSlotSymbols[i].getPosition().x, mRectangle.y - (mDrawLenght - mLenght) * mSlotSymbols[i].getHeight() });
	}
}
