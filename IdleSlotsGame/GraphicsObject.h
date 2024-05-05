#pragma once
#include <raylib.h>
#include <string>
#include "GraphicsObjectManager.h"


class GraphicsObject
{
	friend GraphicsObjectManager;

public:
	void writeTextCenter(const Vector2 pos, const Font font, const Color color, const std::string& text, float size);
	Texture getTexture() { return mTexture; };
private:
	Texture mTexture;

	GraphicsObject(const std::string& filename);
	~GraphicsObject();

};