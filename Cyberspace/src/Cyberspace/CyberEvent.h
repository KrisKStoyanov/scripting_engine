#pragma once
#include <vector>
#include "Core.h"

namespace Cyberspace {
	enum class EventType {
		NONE = 0,
		START = 1,
		MOVE_FORWARD = 2,
		MOVE_BACKWARD = 3,
		MOVE_LEFT = 4,
		MOVE_RIGHT = 5,
		STOP_MOVEMENT = 6,
		EXIT = 7
	};

	enum class EventTag {
		NONE = 0,
		GRAPHICS = 1,
		PHYSICS = 2,
		AUDIO = 3,
		NETWORK = 4
	};

	class CSPACE_API CyberEvent
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
}


