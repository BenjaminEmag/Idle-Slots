#include "Reel.h"
#include "Sprite.h"
#include <raylib.h>
#include "SlotSymbol.h"
#include <iostream>




Reel::Reel(Vector2 pos, std::vector<Sprite> sprites, int lenght, int reelDrawLenght, Rectangle slotMachine) : mPos(pos), mLenght(lenght), mdrawlenght(reelDrawLenght), mRectangle(slotMachine)
{
	Vector2 spritePos{ mPos.x, mPos.y + (lenght - 1) * sprites[0].getHeight()};

	for (int i = 0; i < mdrawlenght; i++)
	{
		int iter = i % sprites.size(); // loops through list

		mSlotSymbols.push_back(SlotSymbol(sprites[iter]));
		mSpriteLocation.push_back(spritePos);
		spritePos.y = spritePos.y - sprites[iter].getHeight();
	}
}


void Reel::draw()
{
	for (int i = 0; i < mdrawlenght; i++)
	{
		int iter = i % mSlotSymbols.size(); // loops through list

		mSlotSymbols[iter].draw();
	}
}

void Reel::spin()
{
	float spinSpeed = 5.0f;

	Vector2 ulSlotMachine{ mRectangle.x, mRectangle.y };
	float slotMachineLenght = mRectangle.height;

	// Update the position of each reel
	for (int i = 0; i < mdrawlenght; i++)
	{
		int iter = i % mSlotSymbols.size();
		mSpriteLocation[i].y = mSpriteLocation[i].y + spinSpeed;


		if (mSpriteLocation[i].y > mRectangle.y + mRectangle.height)
			mSpriteLocation[i].y = mRectangle.y - (mdrawlenght - mLenght) * mSlotSymbols[i].getHeight();
	}
}

void Reel::update()
{
	Vector2 spritePos = mPos;

	for (int i = 0; i < mdrawlenght; i++)
	{
		mSlotSymbols[i].setPosition(mSpriteLocation[i]);
	}
}


