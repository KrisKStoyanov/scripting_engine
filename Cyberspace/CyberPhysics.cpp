#include "CyberPhysics.h"

CyberPhysics::CyberPhysics()
{
}

CyberPhysics::~CyberPhysics()
{
}

void CyberPhysics::Activate()
{
	Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, DefaultAllocatorCallback, DefaultErrorCallback);

	if (Foundation != NULL) {
		bool RecordMemAlloc = true;
		printf("Physx Foundation created.\n");
		VisualDebugger = PxCreatePvd(*Foundation);
		DataTransport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
		Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *Foundation, physx::PxTolerancesScale(), RecordMemAlloc, VisualDebugger);
	}
	else {
		printf("PhysX Foundation initialization failed!");	
	}
	
	if (!Physics) {
		printf("Physics initialization failed!\n");
	}
	Configure();
}

void CyberPhysics::Configure()
{
}

void CyberPhysics::SetupPhysicsCooking()
{
	if (Foundation != NULL) {
		CookingPhysics = PxCreateCooking(PX_PHYSICS_VERSION, *Foundation, physx::PxCookingParams(physx::PxTolerancesScale()));
		if (CookingPhysics != NULL) {
			printf("Cooking Physics initialized successfully!");
		}
		else {
			printf("Cooking Physics initialization failed!");
		}
	}
}

void CyberPhysics::InitExtensionsLibrary()
{
	if (!PxInitExtensions(*Physics, VisualDebugger)) {
		printf("Extension Library initialization failed!");
	}
}

void CyberPhysics::Update()
{
}

void CyberPhysics::Deactivate()
{
	if (Physics != NULL) {
		Physics->release();
	}
	if (Foundation != NULL) {
		Foundation->release();
	}
}
