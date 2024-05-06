#pragma once
#include "Sprite.h"

class SlotSymbol
{
public:
	SlotSymbol(Sprite sprite);

	void draw();
	void update();
	
	void setSlotSymbol(Rectangle rect) { mSprite.setRectangle(rect); };
	void setPosition(Vector2 position) { mSprite.setPosition(position); };
	Vector2 getPosition() { return mSprite.getPosition(); };
	float getWidth() { return mSprite.getWidth(); };
	float getHeight() { return mSprite.getHeight(); };

private:
	Sprite mSprite;
};

