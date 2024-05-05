#pragma once
#include <vector>
#include <raylib.h>
#include "SlotSymbol.h"

class SlotSymbol;
class Sprite;

class Reel
{
public:
	Reel(Vector2 pos, std::vector<Sprite> sprites, int lenght, int reelDrawLenght, Rectangle slotMachine);
	void draw();
	void spin();
	void update();
	void setPosition(Vector2 pos) { mPos = pos; }
	Vector2 getPosition() { return mPos; };
private:
	Vector2 mPos;
	std::vector<SlotSymbol> mSlotSymbols;
	std::vector<Vector2> mSpriteLocation;
	int mLenght;
	int mdrawlenght;
	Rectangle mRectangle;
};