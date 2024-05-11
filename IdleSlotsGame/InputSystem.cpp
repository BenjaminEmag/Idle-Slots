#include "InputSystem.h"
#include "EventSystem.h"
#include <raylib.h>
#include "ClickGameEvent.h"


void InputSystem::update()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Vector2 loc = GetMousePosition();
		ClickGameEvent clickGameEvent(loc);
		EventSystem::getInstance()->fireEvent(clickGameEvent);
	}
}
