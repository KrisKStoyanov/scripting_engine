#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
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
#include "GUIToolkit.h"

namespace Cyberspace {

	class CSPACE_API Renderer
	{
	public:
		static Renderer* Create(const GraphicsProps& _props = GraphicsProps());
		~Renderer();
		void Init(const GraphicsProps& _props);
		void Setup();
		void Draw(Camera* _Camera, Model* _Model, Transform* _Transform, Shader* _Shader);
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, std::unordered_map<std::string, Shader*> _ShaderMap, std::unordered_map<std::string, Entity*> _EntityMap, double _CursorPosX, double _CursorPosY, float _DeltaTime);
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

		bool m_EnableCameraMovement = false;
	private:
		Renderer(const GraphicsProps& _props);
		GraphicsProps m_Props;
	};
}

