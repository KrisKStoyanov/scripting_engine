#pragma once
#include "../../Core.h"

namespace Cyberspace {
	class CSPACE_API PhysicsComponent
	{
	public:
		PhysicsComponent();
		~PhysicsComponent();

		bool Setup();
		void Clear();
	};
}


