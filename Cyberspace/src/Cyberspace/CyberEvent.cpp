#include "CyberEvent.h"

namespace Cyberspace {
	CyberEvent::CyberEvent(EventType _Type) {
		Type = _Type;
	}

	CyberEvent::CyberEvent(EventType _Type, EventTag _FirstTag)
	{
		Type = _Type;
		Tags.push_back(_FirstTag);
	}

	CyberEvent::CyberEvent(EventType _Type, EventTag _FirstTag, EventTag _SecondTag)
	{
		Type = _Type;

		Tags.push_back(_FirstTag);
		Tags.push_back(_SecondTag);
	}

	CyberEvent::CyberEvent(EventType _Type, EventTag _FirstTag, EventTag _SecondTag, EventTag _ThirdTag)
	{
		Type = _Type;

		Tags.push_back(_FirstTag);
		Tags.push_back(_SecondTag);
		Tags.push_back(_ThirdTag);
	}

	CyberEvent::CyberEvent(EventType _Type, EventTag _FirstTag, EventTag _SecondTag, EventTag _ThirdTag, EventTag _FourthTag)
	{
		Type = _Type;

		Tags.push_back(_FirstTag);
		Tags.push_back(_SecondTag);
		Tags.push_back(_ThirdTag);
		Tags.push_back(_FourthTag);
	}

	CyberEvent::CyberEvent()
	{
	}

	CyberEvent::~CyberEvent()
	{
	}
}

