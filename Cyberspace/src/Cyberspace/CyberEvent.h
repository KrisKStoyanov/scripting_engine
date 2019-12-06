#pragma once

namespace Cyberspace {
	enum class CSPACE_API EventType {
		NONE = 0,
		//Blocking
		START,
		PAUSE,
		RESUME,
		EXIT,
		CONNECT,
		DISCONNECT,
		UPDATE_VIDEO_SETTINGS,
		UPDATE_AUDIO_SETTINGS,
		//Non-blocking
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

	enum class CSPACE_API EventTag {
		NONE = 0,
		WINDOW = 1,
		GRAPHICS = 2,
		PHYSICS = 3,
		AUDIO = 4,
		NETWORK = 5,
		GAMEPLAY = 6
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


