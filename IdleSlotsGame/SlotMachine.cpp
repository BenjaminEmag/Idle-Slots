#include "SlotMachine.h"
#include "Reel.h"
#include "Sprite.h"
#include <raylib.h>
#include "GraphicsObjectManager.h"
#include <string>
#include <random>
#include <iostream>

SlotMachine::SlotMachine(Vector2 position, int numReels, int length, GraphicsObjectManager* graphicsObjManager, const std::string key, Vector2 machinDim, Vector2 spriteDim, int spriteCount)
	: mpGrapicObjManagers(graphicsObjManager), mPos(position), mNumReels(numReels), mLenght(length)
{
	mRectangle = { position.x,position.y, machinDim.x, machinDim.y };
	Vector2 reelPosition = position;
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
		Reel reel(reelPosition, sprites, length, spriteCount * 2, mRectangle);
		mReels.push_back(reel);

		reelPosition.x = reelPosition.x + machinDim.x / numReels;
	}

	insertLineFromRow(1);
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
	float offest = 20.0;
	Rectangle drawBox{ mRectangle.x - offest, mRectangle.y - offest, mRectangle.width + offest * 2.0, mRectangle.height + offest * 2.0 };
	DrawRectangleLinesEx(drawBox, 12.0, BLUE);

	BeginScissorMode(mPos.x, mPos.y, mRectangle.width, mRectangle.height);
	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].draw();
	}
	EndScissorMode();


	if (mShowLines)
		DrawLineEx(mLines.at(1).first, mLines.at(1).second, 15.0, RED);
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

	Rectangle* recs = new Rectangle[mSlotSpriteRects.size() * 2.0];

	for (int i = 0; i < mNumReels; i++)
	{
		for (int j = 0; j < mSlotSpriteRects.size() * 2.0; j++)
		{
			int spriteIndex = dis(gen);

			recs[j] = mSlotSpriteRects.at(spriteIndex);
		}

		mReels[i].setVisibleSymbols(recs);
	}
	delete[] recs;
}

void SlotMachine::showLines()
{
	mShowLines = !mShowLines;
}

void SlotMachine::insertLineFromRow(int row)
{
	Rectangle middleRow = getRectFromRow(row);
	Vector2 startPoint{ middleRow.x, middleRow.y - middleRow.height / 2.0f };
	Vector2 endPoint{ middleRow.x + middleRow.width , middleRow.y - middleRow.height / 2.0f };

	mLines.insert({ 1 ,std::make_pair(startPoint,endPoint) });
}

Rectangle SlotMachine::getRectFromRow(int row)
{
	row++;
	return Rectangle{ mRectangle.x , mRectangle.y + row * mSlotSpriteRects[0].height ,mSlotSpriteRects[0].width * mNumReels, mSlotSpriteRects[0].height };
}
