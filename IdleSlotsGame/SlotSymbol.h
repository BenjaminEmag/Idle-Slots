#pragma once
#include "Sprite.h"

class SlotSymbol
{
public:
	SlotSymbol(Sprite sprite);

	void draw();
	void update();

	void setPosition(Vector2 position) { mSprite.setPosition(position); };
	float getWidth() { return mSprite.getWidth(); };
	float getHeight() { return mSprite.getHeight(); };

private:
	Sprite mSprite; 

};

