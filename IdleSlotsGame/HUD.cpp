#include "HUD.h"
#include "GraphicsObjectManager.h"
#include <raylib.h>
#include "Money.h"
#include <string>


HUD::HUD() {}

HUD::~HUD()
{
	delete mpMoney;
}


void HUD::init(int width, int height, Rectangle slotmRect)
{
	mWidth = width;
	mHeight = height;
	mSlotRect = slotmRect;
	mMiddle.x = mWidth / 2.0;
	mMiddle.y = mHeight / 2.0;

	mpMoney = new Money();
}

void HUD::draw(const DrawType& type)
{
	switch (type)
	{
	case GAME_INFO:
		DrawText((MONEY + mpMoney->toString()).c_str(), mSlotRect.x + mSlotRect.width + mWidth * 0.05, mSlotRect.y, 35, BLACK);
	}
}