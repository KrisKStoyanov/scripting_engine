#pragma once
#include "Core.h"
#include <vector>

namespace Cyberspace {
	enum class EventType {
		NONE = 0,
		START,
		PAUSE,
		EXIT,
		VEHICLE_MOVE_FORWARD,
		VEHICLE_MOVE_BACKWARD,
		VEHICLE_MOVE_LEFT,
		VEHICLE_MOVE_RIGHT,
		CAMERA_MOVE_FORWARD,
		CAMERA_MOVE_BACKWARD,
		CAMERA_MOVE_LEFT,
		CAMERA_MOVE_RIGHT,
		UPDATE_POSITIONS
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


