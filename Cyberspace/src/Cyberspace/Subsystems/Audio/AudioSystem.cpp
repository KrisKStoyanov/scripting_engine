#include "cspacepch.h"
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
		FMOD_RESULT result = CoreSystem->update();
		if (result == FMOD_OK) {

			/*if (!_EventQueue.empty()) {
				std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::AUDIO);
				if (Tag != _EventQueue.front()->Tags.end()) {
					_EventQueue.front()->Tags.erase(Tag);
					switch (_EventQueue.front()->Type) {

					case EventType::VEHICLE_MOVE_FORWARD:
						PlaySFX(0);
						if (_EventQueue.front()->Tags.empty()) {
							_EventQueue.pop();
						}
						break;

					case EventType::VEHICLE_MOVE_BACKWARD:
						PlaySFX(0);
						if (_EventQueue.front()->Tags.empty()) {
							_EventQueue.pop();
						}
						break;

					case EventType::VEHICLE_MOVE_LEFT:
						PlaySFX(1);
						if (_EventQueue.front()->Tags.empty()) {
							_EventQueue.pop();
						}
						break;

					case EventType::VEHICLE_MOVE_RIGHT:
						PlaySFX(1);
						if (_EventQueue.front()->Tags.empty()) {
							_EventQueue.pop();
						}
						break;
					default:
						break;
					}
				}
			}*/
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

	void AudioSystem::PlayBGM(int _index)
	{
		CoreSystem->playSound(BGM[_index], NULL, false, &BGM_Channel);
	}
	void AudioSystem::PlaySFX(int _index)
	{
		CoreSystem->playSound(SFX[_index], NULL, false, &BGM_Channel);
	}

	void AudioSystem::SetVolumeBGM(float _vol)
	{
		BGM_Channel->setVolume(_vol);
	}

	void AudioSystem::SetVolumeSFX(float _vol)
	{
		SFX_Channel->setVolume(_vol);
	}

	void AudioSystem::ToggleMuteBGM(bool _muted)
	{
		BGM_Channel->setMute(_muted);
	}
	void AudioSystem::ToggleMuteSFX(bool _muted)
	{
		SFX_Channel->setMute(_muted);
	}
}

