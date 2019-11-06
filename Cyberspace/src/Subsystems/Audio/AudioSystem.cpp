#include "AudioSystem.h"

AudioSystem::AudioSystem(bool& _InitStatus)
{
	_InitStatus = Init();
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Init()
{
	FMOD_RESULT EventResult;

	EventResult = FMOD::System_Create(&CoreSystem);
	if (EventResult != FMOD_OK) {
		printf("FMOD Error!\n)(%d)\n", EventResult);
		return false;
	}

	EventResult = CoreSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (EventResult) {
		printf("FMOD Error!\n(%d)\n", EventResult);
		return false;
	}
	printf("Audio system created and initialized\n");

	CoreSystem->createSound("../External Resources/Audio/TitleScreenTrack.wav", FMOD_LOOP_OFF, NULL, &BGM[0]);
	if (BGM[0] != NULL) {
		printf("Title screen track loaded\n");
		BGM[0]->setDefaults(16400, 0);
	}

	return true;
}

void AudioSystem::Update(std::vector<Entity*> _EntityCollection)
{
	for (Entity* E : _EntityCollection) {
		if (E->m_Audio != NULL) {

		}
	}

	//if (!_Events.empty()) {
	//	for (int i = 0; i < _Events.back()->Tags.size(); ++i) {
	//		if (_Events.back()->Tags[i] == EventTag::AUDIO) {

	//		}
	//	}
	//}
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