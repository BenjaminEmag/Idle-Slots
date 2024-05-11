#pragma once
#include <raylib.h>
#include "Event.h"

class InputSystem
{
public:
	~InputSystem() = default;
	InputSystem() = default;

	void update();
};