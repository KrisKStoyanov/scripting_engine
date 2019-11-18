#include "cspacepch.h"
#include "PhysicsSystem.h"

namespace Cyberspace {
	PhysicsSystem* PhysicsSystem::Create(const PhysicsProps& _props)
	{
		return new PhysicsSystem(_props);
	}
	PhysicsSystem::PhysicsSystem(const PhysicsProps& _props)
	{
		Init(_props);
	}

	PhysicsSystem::~PhysicsSystem()
	{
		Terminate();
	}

	void PhysicsSystem::Init(const PhysicsProps& _props)
	{
		Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, DefaultAllocator, DefaultErrorCallback);

		if (!Foundation) {
			printf("Physx Foundation initialization failed.\n");
		}
		bool RecordMemAlloc = true;
		printf("Physx Foundation created.\n");
		VisualDebugger = PxCreatePvd(*Foundation);
		physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
		VisualDebugger->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
		Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *Foundation, physx::PxTolerancesScale(), RecordMemAlloc, VisualDebugger);
		if (!Physics) {
			printf("Physics initialization failed!\n");
		}
		printf("Physx Physics setup.\n");

		Configure();
	}

	void PhysicsSystem::Configure()
	{
		physx::PxSceneDesc SceneDescriptor(Physics->getTolerancesScale());
		SceneDescriptor.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
		Dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
		SceneDescriptor.cpuDispatcher = Dispatcher;
		SceneDescriptor.filterShader = physx::PxDefaultSimulationFilterShader;
		Scene = Physics->createScene(SceneDescriptor);

		physx::PxPvdSceneClient* VisDebugClient = Scene->getScenePvdClient();
		if (VisDebugClient) {
			VisDebugClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
			VisDebugClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
			VisDebugClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
		}
		Material = Physics->createMaterial(0.5f, 0.5f, 0.6f);
		physx::PxRigidStatic* GroundPlane = physx::PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 0), *Material);
		Scene->addActor(*GroundPlane);
		Scene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
		Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 2.0f);
	}


	bool PhysicsSystem::SetupPhysicsCooking()
	{
		if (Foundation != NULL) {
			CookingPhysics = PxCreateCooking(PX_PHYSICS_VERSION, *Foundation, physx::PxCookingParams(physx::PxTolerancesScale()));
			if (CookingPhysics != NULL) {
				printf("Cooking Physics initialized successfully!");
				return true;
			}
			printf("Cooking Physics initialization failed!");
			return false;
		}
		return false;
	}

	bool PhysicsSystem::InitExtensionsLibrary()
	{
		if (!PxInitExtensions(*Physics, VisualDebugger)) {
			printf("Extension Library initialization failed!");
			return false;
		}
		printf("Extension Library initialization successfully!");
		return true;
	}

	void PhysicsSystem::Update(std::queue<CyberEvent*> _EventQueue, std::vector<Entity*> _EntityCollection)
	{
		if (!_EventQueue.empty()) {
			std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::PHYSICS);
			if (Tag != _EventQueue.front()->Tags.end()) {
				_EventQueue.front()->Tags.erase(Tag);
				switch (_EventQueue.front()->Type) {
				case EventType::VEHICLE_MOVE_FORWARD:
					//TestEntity->Position += glm::vec3(0, 0.001f, 0);
					printf("MOVE_FORWARD EVENT\n");
					break;
				case EventType::VEHICLE_MOVE_BACKWARD:
					//TestEntity->Position += glm::vec3(0, -0.001f, 0);
					printf("MOVE_BACKWARD EVENT\n");
					break;
				case EventType::VEHICLE_MOVE_LEFT:
					//TestEntity->Position += glm::vec3(-0.001f, 0, 0);
					printf("MOVE_LEFT EVENT\n");
					break;
				case EventType::VEHICLE_MOVE_RIGHT:
					//TestEntity->Position += glm::vec3(0.001f, 0, 0);
					printf("MOVE_RIGHT EVENT\n");
					break;
				default:
					break;
				}
				if (_EventQueue.front()->Tags.empty()) {
					_EventQueue.pop();
				}
			}
		}
		for (Entity* E : _EntityCollection) {
			if (E->m_PSX != NULL) {

			}
		}
	}

	//void CyberPhysics::HandleEvent(CyberEvent* _Event)
	//{
	//	if (_Event->Type == EventType::MOVE_FORWARD) {
	//		//main character vehicle move forward
	//	}
	//	if (_Event->Type == EventType::MOVE_BACKWARD) {
	//		//main character vehicle move backward
	//	}
	//	if (_Event->Type == EventType::MOVE_LEFT) {
	//		//main character vehicle move left
	//	}
	//	if (_Event->Type == EventType::MOVE_RIGHT) {
	//		//main character vehicle move right
	//	}
	//}

	void PhysicsSystem::Terminate()
	{
		if (Scene) {
			Scene->release();
			Scene = NULL;
		}
		if (Dispatcher) {
			Dispatcher->release();
			Dispatcher = NULL;
		}
		if (Physics) {
			Physics->release();
			Physics = NULL;
		}
		if (VisualDebugger) {
			physx::PxPvdTransport* transport = VisualDebugger->getTransport();
			VisualDebugger->release();
			VisualDebugger = NULL;
			if (transport) {
				transport->release();
				transport = NULL;
			}
		}
		if (Foundation) {
			Foundation->release();
			Physics = NULL;
		}
	}
}

