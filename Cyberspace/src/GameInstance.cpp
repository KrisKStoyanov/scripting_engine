#include "GameInstance.h"

GameInstance::GameInstance()
{

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
	//AddEntity("TestEntity", EntityVerts, EntityIndices);
	//Update();
}

//void GameInstance::AddEntity(std::string _EntityName, std::vector<Vertex> _EntityVerts, std::vector<GLuint> _EntityIndices)
//{
//	EntityCollection[_EntityName] = new Entity(_EntityVerts, _EntityIndices);
//	EntityCollection[_EntityName]->Setup();
//}

void GameInstance::Update()
{
}

void GameInstance::Clear()
{
}

void GameInstance::Exit()
{
}
