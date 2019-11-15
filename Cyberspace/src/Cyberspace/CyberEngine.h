#pragma once
#include "Core.h"
#include "Entity.h"
#include "./Subsystems/Graphics/Renderer.h"
#include "./Subsystems/Interface/UIController.h"
#include "./Subsystems/Networking/CyberNet.h"
#include "./Subsystems/Audio/AudioSystem.h"
#include "./Subsystems/Physics/PhysicsSystem.h"
#include "./Subsystems/AssetManagement/AssetManager.h"
#include "./Subsystems/GameManagement/GameManager.h"

#include "CyberEvent.h"
#include "EventListener.h"
#include "Core/Timestep.h"
#include "Subsystems/Logging/Log.h"

namespace Cyberspace {

	struct EngineProps {
		UIProps m_UIProps;
		GraphicsProps m_GraphicsProps;
		PhysicsProps m_PhysicsProps;
		AudioProps m_AudioProps;
		NetworkProps m_NetProps;
		AMProps m_AMProps;
		GMProps m_GMProps;

		EngineProps(
			UIProps _uiProps = UIProps(),
			GraphicsProps _gProps = GraphicsProps(),
			PhysicsProps _pProps = PhysicsProps(),
			AudioProps _aProps = AudioProps(),
			NetworkProps _netProps = NetworkProps(),
			AMProps _amProps = AMProps(),
			GMProps _gmProps = GMProps()) :
			m_UIProps(_uiProps),
			m_GraphicsProps(_gProps),
			m_PhysicsProps(_pProps),
			m_AudioProps(_aProps),
			m_NetProps(_netProps),
			m_AMProps(_amProps),
			m_GMProps(_gmProps) {}
	};

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

	private:
		CyberEngine(const EngineProps& _props);
		std::queue<CyberEvent*> BlockingEventQueue;
		std::queue<CyberEvent*> EventQueue;

		std::unique_ptr<UIController> m_UIController;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<PhysicsSystem> m_PhysicsSystem;
		std::unique_ptr<AudioSystem> m_AudioSystem;
		std::unique_ptr<CyberNet> m_NetSystem;
		std::unique_ptr<AssetManager> m_AssetManager;
		std::unique_ptr<GameManager> m_GameManager;

		bool m_Tick = false;
	};
}


