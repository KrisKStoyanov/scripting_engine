#pragma once
#include <vector>

enum class EventType {
	NONE = 0,
	START = 1,
	MOVE_FORWARD = 2,
	MOVE_BACKWARD = 3,
	MOVE_LEFT = 4,
	MOVE_RIGHT = 5,
	EXIT = 6
};

enum class EventTag {
	NONE = 0,
	GRAPHICS = 1,
	PHYSICS = 2,
	AUDIO = 3,
	NETWORK = 4
};

class CyberEvent
{
public:
	CyberEvent(EventType _Type);
	CyberEvent(EventType _Type, EventTag _FirstTag);
	CyberEvent(EventType _Type, EventTag _FirstTag, EventTag _SecondTag);
	CyberEvent(EventType _Type, EventTag _FirstTag, EventTag _SecondTag, EventTag _ThirdTag);
	CyberEvent(EventType _Type, EventTag _FirstTag, EventTag _SecondTag, EventTag _ThirdTag, EventTag _FourthTag);
	CyberEvent();
	~CyberEvent();
	EventType Type;
	std::vector<EventTag> Tags;
};

