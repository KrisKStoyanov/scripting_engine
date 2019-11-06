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
#include "Shader.h"

#include "../../Entity.h"
#include "../../CyberEvent.h"
#include "../../EventList.h"
#include "Camera.h"
#include "Material.h"
#include <queue>

enum class ShaderType {
	BASIC = 0,
	TEXTURE = 1,
	SKYBOX = 2
};

class Renderer
{
public:
	Renderer(bool& _InitStatus, int _WindowWidth, int _WindowHeight);
	~Renderer();
	bool Init(int _WindowWidth, int _WindowHeight);
	void Draw(Camera* _Camera, Entity* _Entity, Shader* _Shader);
	void Update(std::queue<CyberEvent*>& _EventQueue, std::vector<Entity*> _EntityCollection, double _CursorPosX, double _CursorPosY, float _DeltaTime);
	void Terminate();

	Shader* SetupShader(const GLchar* _VertexShaderPath, const GLchar* _FragmentShaderPath, ShaderType _Type);
	Shader* BasicShader = NULL;
	Shader* TextureShader = NULL;
	Shader* SkyboxShader = NULL;

	void(*MoveForward)(EventType) = MoveForwardEvent;
	void(*MoveBackward)(EventType) = MoveBackwardEvent;
	void(*MoveLeft)(EventType) = MoveLeftEvent;
	void(*MoveRight)(EventType) = MoveRightEvent;

	Camera* MainCamera = NULL;
};

