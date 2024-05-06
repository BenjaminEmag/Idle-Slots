#pragma once
#include <raylib.h>

class GraphicsObject;

class Sprite
{
public:
	Sprite(GraphicsObject* graphics, const Vector2 pos, float width, float height);
	GraphicsObject* getGraphicsObject() const { return mpGraphicsObj; };
	float getWidth() const { return mRectangle.width; };
	float getHeight() const { return mRectangle.height; };
	Rectangle getRectangle() const { return mRectangle; };
	void setPosition(Vector2 position) { mPos = position; };
	Vector2 getPosition() { return mPos; };
	Vector2 getCenter();
	void setRectangle(Rectangle rect) { mRectangle = rect; };
	void draw();
	
private:
	GraphicsObject* mpGraphicsObj = nullptr;
	Vector2 mPos = Vector2{ 0.0f,0.0f };
	Rectangle mRectangle;
};