#pragma once
#include "Entity.h"
#include "Subsystems/Graphics/Renderer.h"
#include "Subsystems/Interface/EngineWindow.h"
#include "Subsystems/Networking/CyberNet.h"
#include "Subsystems/Audio/AudioSystem.h"
#include "Subsystems/Physics/PhysicsSystem.h"
#include "Subsystems/AssetManagement/AssetManager.h"
#include "Subsystems/Scripting/Script.h"
#include "./Subsystems/GameManagement/GameManager.h"

#include "CyberEvent.h"
#include "Core/Timestep.h"
#include "Subsystems/Logging/Log.h"
#include "../EngineProps.h"

namespace Cyberspace {

	class CSPACE_API CyberEngine
	{
	public:
		static CyberEngine* Create(const EngineProps& _props = EngineProps());

		~CyberEngine();

		void Init(const EngineProps& _props);
		void OnUpdate(const Timestep _ts);
		void Terminate();

		inline bool GetTick() { return m_Tick; }
		inline void SetTick(const bool _tick) { m_Tick = _tick; }
		EngineProps m_Props;
		EngineState m_State;
	private:
		CyberEngine(const EngineProps& _props);
		std::queue<CyberEvent*> BlockingEventQueue;
		std::queue<CyberEvent*> EventQueue;

		std::unique_ptr<EngineWindow> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<GUIToolkit> m_GUI;
		std::unique_ptr<PhysicsSystem> m_PhysicsSystem;
		std::unique_ptr<AudioSystem> m_AudioSystem;
		std::unique_ptr<CyberNet> m_NetSystem;
		std::unique_ptr<AssetManager> m_AssetManager;
		std::unique_ptr<GameManager> m_GameManager;

		bool m_Tick = false;
	};
}


