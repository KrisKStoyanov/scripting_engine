#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PxPhysicsAPI.h"
#include "../../Entity.h"
#include "../../CyberEvent.h"
#include "../../../EngineProps.h"

//LocalHost for visual debugger init process
constexpr auto PVD_HOST = "127.0.0.1";

namespace Cyberspace {

	class CSPACE_API PhysicsSystem
	{
	public:
		static PhysicsSystem* Create(const PhysicsProps& _props = PhysicsProps());
		PhysicsSystem(const PhysicsProps& _props);
		~PhysicsSystem();
		void Init(const PhysicsProps& _props);
		void Configure();
		bool SetupPhysicsCooking();
		bool InitExtensionsLibrary();
		void Update(std::queue<CyberEvent*> _EventQueue, std::vector<Entity*> _EntityCollection);
		/*void HandleEvent(CyberEvent* _Event);*/
		void Terminate();

		physx::PxDefaultErrorCallback DefaultErrorCallback;
		physx::PxDefaultAllocator DefaultAllocator;
		physx::PxFoundation* Foundation = NULL;
		physx::PxPhysics* Physics = NULL;

		physx::PxDefaultCpuDispatcher* Dispatcher = NULL;
		physx::PxScene* Scene = NULL;
		physx::PxMaterial* Material = NULL;

		physx::PxPvd* VisualDebugger = NULL;

		physx::PxCooking* CookingPhysics = NULL;
	};
}


