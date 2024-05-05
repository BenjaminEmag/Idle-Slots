#include "SlotMachine.h"
#include "GraphicsObject.h"
#include "Reel.h"
#include "Sprite.h"
#include <raylib.h>
#include "GraphicsObjectManager.h"
#include <string>

SlotMachine::SlotMachine(Vector2 position, int numReels, int lenght, GraphicsObjectManager* graphicsObjManager, const std::string key, Vector2 machinDim, Vector2 spriteDim, int spriteCount)
	: mGrapicObjManagers(graphicsObjManager), mPos(position), mNumReels(numReels)
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
	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].spin();
	}
}

void SlotMachine::stop()
{

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
	switch (mState)
	{
	case SlotMachine::START:
		break;
	case SlotMachine::SPIN:
		spin();
		break;
	case SlotMachine::STOP:
		break;
	default:
		break;
	}

	for (int i = 0; i < mNumReels; i++)
	{
		mReels[i].update();
	}
}
