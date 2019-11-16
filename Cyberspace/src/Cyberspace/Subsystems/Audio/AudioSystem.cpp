#include "AudioSystem.h"

namespace Cyberspace {
	AudioSystem* AudioSystem::Create(const AudioProps& _props)
	{
		return new AudioSystem(_props);
	}
	AudioSystem::AudioSystem(const AudioProps& _props)
	{
		Init(_props);
	}

	AudioSystem::~AudioSystem()
	{
		Terminate();
	}

	void AudioSystem::Init(const AudioProps& _props)
	{
		FMOD_RESULT EventResult;

		EventResult = FMOD::System_Create(&CoreSystem);
		if (EventResult != FMOD_OK) {
			printf("FMOD Error!\n)(%d)\n", EventResult);
		}

		EventResult = CoreSystem->init(512, FMOD_INIT_NORMAL, 0);
		if (EventResult) {
			printf("FMOD Error!\n(%d)\n", EventResult);
		}
		printf("Audio system created and initialized\n");

		CoreSystem->createSound(_props.TitleScreenBGMFilePath, FMOD_LOOP_OFF, NULL, &BGM[0]);
		if (BGM[0] != NULL) {
			printf("Title screen track loaded\n");
			BGM[0]->setDefaults(16400, 0);
		}
	}

	void AudioSystem::Configure(const AudioProps& _props)
	{
	}

	void AudioSystem::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		if (!_BlockingEventQueue.empty()) {
			std::vector<EventTag>::iterator Tag = std::find(_BlockingEventQueue.front()->Tags.begin(), _BlockingEventQueue.front()->Tags.end(), EventTag::GRAPHICS);
			if (Tag != _BlockingEventQueue.front()->Tags.end()) {
				_BlockingEventQueue.front()->Tags.erase(Tag);
				switch (_BlockingEventQueue.front()->Type) {
				case EventType::UPDATE_SETTINGS:
					Configure(m_Props);
					if (_BlockingEventQueue.front()->Tags.empty()) {
						_BlockingEventQueue.pop();
					}
					break;

				}
			}
		}
	}

	void AudioSystem::HandleEvent(CyberEvent* _Event)
	{

	}

	void AudioSystem::Terminate()
	{
		if (CoreSystem != NULL) {
			CoreSystem->release();
		}
	}

	void AudioSystem::PlayBGM(int _Index)
	{
		CoreSystem->playSound(BGM[_Index], NULL, false, &BGM_Channel);
	}

	void AudioSystem::PlaySFX(int _Index)
	{
		CoreSystem->playSound(SFX[_Index], NULL, false, &BGM_Channel);
	}
}

