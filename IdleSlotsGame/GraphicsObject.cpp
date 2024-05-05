#include "GraphicsObject.h"

GraphicsObject::GraphicsObject(const std::string& filename)
{
	mTexture = LoadTexture(filename.c_str());
}

GraphicsObject::~GraphicsObject()
{
	UnloadTexture(mTexture);
}

void GraphicsObject::writeTextCenter(const Vector2 pos, const Font font, const Color color, const std::string& text, float size)
{
	Vector2 textWidth = MeasureTextEx(font, text.c_str(), size, 1);

	int textStartX = pos.x - textWidth.x / 2.0;
	int textStartY = pos.y - size / 2;

	Vector2 loc = { textStartX, textStartY };
	DrawTextEx(font, text.c_str(), loc, size, NULL, color);
}


