#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PxPhysicsAPI.h"

//LocalHost for visual debugger init process
#define PVD_HOST "127.0.0.1"

class CyberPhysics
{
public:
	CyberPhysics();
	~CyberPhysics();
	void Activate();
	void Configure();
	void SetupPhysicsCooking();
	void InitExtensionsLibrary();
	void Update();
	void Deactivate();

	physx::PxDefaultErrorCallback DefaultErrorCallback;
	physx::PxDefaultAllocator DefaultAllocatorCallback;
	physx::PxFoundation* Foundation = NULL;
	physx::PxPvd* VisualDebugger = NULL;
	physx::PxPvdTransport* DataTransport = NULL;
	physx::PxPhysics* Physics = NULL;

	physx::PxCooking* CookingPhysics = NULL;
};

