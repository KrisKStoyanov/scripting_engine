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
#include "../AssetManagement/Shader.h"

#include "../../Entity.h"
#include "../../CyberEvent.h"
#include "Camera.h"
#include "Material.h"
#include "Skybox.h"
#include "Light.h"
#include <queue>
#include <unordered_map>

namespace Cyberspace {

	struct GraphicsProps {
		unsigned int Width;
		unsigned int Height;
		GraphicsProps(unsigned int _width = 1280, unsigned int _height = 720) 
		: Width (_width), Height (_height) {}
	};

	class Renderer
	{
	public:
		static Renderer* Create(const GraphicsProps& _props = GraphicsProps());
		Renderer(const GraphicsProps& _props);
		~Renderer();
		void Init(const GraphicsProps& _props);
		void Setup(int _WindowWidth, int _WindowHeight);
		void Draw(Camera* _Camera, Entity* _Entity, Shader* _Shader);
		void OnUpdate(std::queue<CyberEvent*>& _EventQueue, std::unordered_map<std::string, Shader*> _ShaderMap, std::map<EntityTag, Entity*> _EntityCollection, double _CursorPosX, double _CursorPosY, std::vector<glm::vec3>& _updatedPositions, float _DeltaTime);
		void Terminate();

		Light* DirLight = NULL;
		Light* PointLight = NULL;
		Light* SpotLight = NULL;

		//void(*MoveForward)(EventType) = MoveForwardEvent;
		//void(*MoveBackward)(EventType) = MoveBackwardEvent;
		//void(*MoveLeft)(EventType) = MoveLeftEvent;
		//void(*MoveRight)(EventType) = MoveRightEvent;

		Camera* MainCamera = NULL;
		Skybox* MainSkybox = NULL;
	};
}

