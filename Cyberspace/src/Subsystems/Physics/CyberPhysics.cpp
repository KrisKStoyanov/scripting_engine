#include "CyberPhysics.h"

CyberPhysics::CyberPhysics(bool& _InitStatus)
{
	_InitStatus = Init();
}

CyberPhysics::~CyberPhysics()
{
}

bool CyberPhysics::Init()
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
		return false;
	}
	
	if (!Physics) {
		printf("Physics initialization failed!\n");
		return false;
	}
	return true;
}


bool CyberPhysics::SetupPhysicsCooking()
{
	if (Foundation != NULL) {
		CookingPhysics = PxCreateCooking(PX_PHYSICS_VERSION, *Foundation, physx::PxCookingParams(physx::PxTolerancesScale()));
		if (CookingPhysics != NULL) {
			printf("Cooking Physics initialized successfully!");
			return true;
		}
		else {
			printf("Cooking Physics initialization failed!");
			return false;
		}
	}
}

bool CyberPhysics::InitExtensionsLibrary()
{
	if (!PxInitExtensions(*Physics, VisualDebugger)) {
		printf("Extension Library initialization failed!");
		return false;
	}
	printf("Extension Library initialization successfully!");
	return true;
}

void CyberPhysics::Update()
{
}

void CyberPhysics::Terminate()
{
	if (Physics != NULL) {
		Physics->release();
	}
	if (Foundation != NULL) {
		Foundation->release();
	}
}
