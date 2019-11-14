#pragma once
#include "CyberEvent.h"
#include <queue>

namespace Cyberspace {
	class CSPACE_API EventListener
	{
	public:
		EventListener();
		~EventListener();
		std::queue<CyberEvent*> EventQueue;
	};
}


