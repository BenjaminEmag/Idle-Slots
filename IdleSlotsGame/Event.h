#pragma once

#include <string>

using namespace std;

enum EventType
{
	INVALID_EVENT_TYPE = -1,
	CLICK_GAME_EVENT,
	REEL_STOP_EVENT,
	NUM_EVENTS
};

class Event
{
public:
	Event(EventType type);
	virtual ~Event();

	EventType getType() const { return mType; };

private:
	EventType mType;

};