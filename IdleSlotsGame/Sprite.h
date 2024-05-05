#pragma once
#include <raylib.h>

class GraphicsObject;

class Sprite
{
public:
	Sprite(GraphicsObject* graphics, const Vector2 pos, float width, float height);
	GraphicsObject* getGraphicsObject() const { return mpGraphicsObj; };
	const Vector2 getSourceLoc() const { return mPos; };
	float getWidth() const { return mRectangle.width; };
	float getHeight() const { return mRectangle.height; };
	Rectangle getRectangle() const { return mRectangle; };
	void setPosition(Vector2 position) { mPos = position; };
	Vector2 getCenter();
	void draw();

private:
	GraphicsObject* mpGraphicsObj = nullptr;
	Vector2 mPos = Vector2{ 0.0f,0.0f };
	Rectangle mRectangle;
};