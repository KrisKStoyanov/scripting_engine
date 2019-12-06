#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fmod.hpp>
#include <fmod_studio.hpp>

#include "../../Entity.h"
#include "../../CyberEvent.h"
#include "../../../EngineProps.h"

namespace Cyberspace {

	class CSPACE_API AudioSystem
	{
	public:
		static AudioSystem* Create(const AudioProps& _props = AudioProps());
		AudioSystem(const AudioProps& _props);
		~AudioSystem();
		void Init(const AudioProps& _props);
		void OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue);
		void Terminate();
		void PlayBGM(int _index);
		void PlaySFX(int _index);
		void ToggleMuteBGM(bool _muted);
		void ToggleMuteSFX(bool _muted);
		void SetVolumeBGM(float _vol, float _mVol);
		void SetVolumeSFX(float _vol, float _mVol);
		bool GetPlayStatus(FMOD::Channel* _channel);

		float m_MasterVol = 1.0f;
		float m_BGMVol = 1.0f;
		float m_SFXVol = 1.0f;

		bool m_MutedBGM;
		bool m_MutedSFX;

		FMOD::System* CoreSystem = NULL;
		FMOD::Sound* BGM[2];
		FMOD::Sound* SFX[2];
		//std::vector<FMOD::Sound*> BGM;
		//std::vector<FMOD::Sound*> SFX;

		FMOD::Channel* BGM_Channel = NULL;
		FMOD::Channel* SFX_Channel = NULL;
	};
}

