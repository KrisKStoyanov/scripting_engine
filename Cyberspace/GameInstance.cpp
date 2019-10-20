#include "GameInstance.h"

GameInstance::GameInstance(GLFWwindow* _GameWindow)
{
	GameWindow = _GameWindow;
}

GameInstance::~GameInstance()
{
}

void GameInstance::Start()
{
	Active = true;
	Configure();
}

void GameInstance::Configure()
{
	std::vector<Vertex> EntityVerts({
		{{ 0.5f,  0.5f, 0.0f, }, {1.0f, 0.0f, 0.0f, 1.0f }},
		{{ 0.5f, -0.5f, 0.0f, }, {1.0f, 1.0f, 0.0f, 1.0f }},
		{{ -0.5f, -0.5f, 0.0f, }, {1.0f, 0.0f, 1.0f, 1.0f }},
		{{ -0.5f,  0.5f, 0.0f }, {0.0f, 1.0f, 1.0f, 1.0f }}
	});
	std::vector<GLuint> EntityIndices({ 0,1,3, 1,2,3 });
	AddEntity("TestEntity", EntityVerts, EntityIndices);
	//Update();
}

void GameInstance::AddEntity(std::string _EntityName, std::vector<Vertex> _EntityVerts, std::vector<GLuint> _EntityIndices)
{
	EntityCollection[_EntityName] = new Entity(_EntityVerts, _EntityIndices);
	EntityCollection[_EntityName]->Setup();
}

void GameInstance::Update()
{
}

void GameInstance::Clear()
{
}

void GameInstance::Exit()
{
}
