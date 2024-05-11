#pragma once
#include "Event.h"
#include <raylib.h>

class ClickGameEvent : public Event
{
public:
	ClickGameEvent(const Vector2 pos);
	Vector2 mPos{ 0.0f,0.0f };
};