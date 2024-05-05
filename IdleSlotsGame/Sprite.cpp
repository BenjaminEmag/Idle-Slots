#include "Sprite.h"
#include "GraphicsObject.h"

Sprite::Sprite(GraphicsObject* graphics, const Vector2 pos, float width, float height) : mpGraphicsObj(graphics), mPos(pos)
{
	mRectangle = { pos.x,pos.y,width,height };
}

Vector2 Sprite::getCenter()
{
	return Vector2{ mRectangle.width / 2.0f, mRectangle.height / 2.0f };
}

void Sprite::draw()
{
	DrawTextureRec(mpGraphicsObj->getTexture(), mRectangle , mPos, WHITE);
}
