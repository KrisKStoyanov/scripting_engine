#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <enet/enet.h>

#include "Entity.h"
#include "./Subsystems/Graphics/Renderer.h"
#include "./Subsystems/Interface/UISystem.h"
#include "./Subsystems/Networking/CyberNet.h"
#include "./Subsystems/Audio/AudioSystem.h"
#include "./Subsystems/Physics/PhysicsSystem.h"
#include "./Subsystems/Window/EngineWindow.h"
#include "./Subsystems/GameManager/GameManager.h"

#include "CyberEvent.h"

#include "./Subsystems/Graphics/Model.h"

namespace Cyberspace {

	struct EngineProps {
		WindowProps m_WindowProps;
		GraphicsProps m_GraphicsProps;
		PhysicsProps m_PhysicsProps;
		AudioProps m_AudioProps;
		UIProps m_UIProps;
		NetworkProps m_NetProps;

		EngineProps(
			WindowProps _wProps = WindowProps(),
			GraphicsProps _gProps = GraphicsProps(),
			PhysicsProps _pProps = PhysicsProps(),
			AudioProps _aProps = AudioProps(),
			UIProps _uiProps = UIProps(),
			NetworkProps _netProps = NetworkProps()) :
			m_WindowProps(_wProps),
			m_GraphicsProps(_gProps),
			m_PhysicsProps(_pProps),
			m_AudioProps(_aProps),
			m_UIProps(_uiProps),
			m_NetProps(_netProps) {}
	};

	class CSPACE_API CyberEngine
	{
	public:
		static CyberEngine* Create(const EngineProps& _props = EngineProps());
		CyberEngine(const EngineProps& _props);
		~CyberEngine();

		void Init(const EngineProps& _props);
		void Configure();
		float ComputeDeltaTime(float _CurrentFrame);
		void OnUpdate();
		void Terminate();

		bool m_Running = true;

		std::map<EntityTag, Entity*> EntityCollection;
		std::queue<CyberEvent*> EventQueue;

	private:
		std::unique_ptr<EngineWindow> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<PhysicsSystem> m_PhysicsSystem;
		std::unique_ptr<AudioSystem> m_AudioSystem;
		std::unique_ptr<UISystem> m_UISystem;
		std::unique_ptr<CyberNet> m_NetSystem;
		std::unique_ptr<GameManager> m_GameManager;
		float DeltaTime = 0.0f, LastFrameTime = 0.0f;
	};
}


