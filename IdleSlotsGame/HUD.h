#pragma once
#include "raylib.h"
#include <string>

class Money;

class HUD
{
public:
	enum DrawType
	{
		GAME_INFO
	};

	HUD();
	~HUD();

	void init(int width, int height, Rectangle slotmRect);
	void draw(const DrawType& type);

	Money* getMoney() { return mpMoney; };
private:
	int mWidth = 0;
	int mHeight = 0;
	Vector2 mMiddle;
	Rectangle mSlotRect;
	int mFontSize = 45;
	Money* mpMoney = nullptr;

	std::string MONEY = "$ ";
};