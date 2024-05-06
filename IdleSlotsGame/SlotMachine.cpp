#include "SlotMachine.h"
#include "Reel.h"
#include "Sprite.h"
#include <raylib.h>
#include "GraphicsObjectManager.h"
#include <string>
#include <random>

SlotMachine::SlotMachine(Vector2 position, int numReels, int lenght, GraphicsObjectManager* graphicsObjManager, const std::string key, Vector2 machinDim, Vector2 spriteDim, int spriteCount)
	: mpGrapicObjManagers(graphicsObjManager), mPos(position), mNumReels(numReels), mLenght(lenght)
{
	mRectangle = { position.x,position.y, machinDim.x, machinDim.y };
	Vector2 reelPositon = position;
	std::vector<Sprite> sprites;

	for (int i = 0; i < spriteCount; i++)
	{
		Vector2 pos;
		pos.x = i * spriteDim.x;
		pos.y = spriteDim.y;

		Sprite sprite(graphicsObjManager->getObject(key), pos, spriteDim.x, spriteDim.y);
		mSlotSpriteRects.push_back(sprite.getRectangle());
		sprites.push_back(sprite);
	}

	for (int i = 0; i < numReels; i++)
	{
		Reel reel(reelPositon, sprites, lenght, spriteCount * 2, mRectangle);
		mReels.push_back(reel);

		reelPositon.x = reelPositon.x + machinDim.x / numReels;
	}

	start();
}

void SlotMachine::start()
{
	Vector2 reelPosition = mPos;

	float reelWidth = mRectangle.width / mNumReels;
	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].setPosition(reelPosition);
		reelPosition.x += reelWidth;
	}
}

void SlotMachine::spin()
{
	float totalTime = mTotalSpinLenght;
	float timeInterval = totalTime / mNumReels;
	float spinTime = timeInterval;
	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].startSpin(spinTime, mSpinSpeed);
		spinTime += timeInterval;
	}

	calculateSpinResult();
}

void SlotMachine::stopSpin()
{
	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].stop();
	}
}

void SlotMachine::draw()
{
	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].draw();
	}
}

void SlotMachine::update()
{
	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].update();
	}
}

void SlotMachine::calculateSpinResult()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, mSlotSpriteRects.size() - 1);
	
	Rectangle* recs = new Rectangle[mLenght];

	bool shouldRepeatTiles = false;

	for (int i = 0; i < mNumReels; i++)
	{
		for (int j = 0; j < mLenght; j++)
		{
			int spriteIndex = dis(gen);

			recs[j] = mSlotSpriteRects.at(spriteIndex);
		}

		mReels[i].setVisibleSymbols(recs);
	}
}
