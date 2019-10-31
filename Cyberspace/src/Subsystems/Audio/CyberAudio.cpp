#include "CyberAudio.h"

CyberAudio::CyberAudio(bool& _InitStatus)
{
	_InitStatus = Init();
}

CyberAudio::~CyberAudio()
{
}

bool CyberAudio::Init()
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

void CyberAudio::Update(std::vector<Entity*> _EntityCollection)
{
	for (Entity* E : _EntityCollection) {
		if (E->Audio_Comp != NULL) {

		}
	}

	//if (!_Events.empty()) {
	//	for (int i = 0; i < _Events.back()->Tags.size(); ++i) {
	//		if (_Events.back()->Tags[i] == EventTag::AUDIO) {

	//		}
	//	}
	//}
}

void CyberAudio::HandleEvent(CyberEvent* _Event)
{

}

void CyberAudio::Terminate()
{
	if (CoreSystem != NULL) {
		CoreSystem->release();
	}
}

void CyberAudio::PlayBGM(int _Index)
{
	CoreSystem->playSound(BGM[_Index], NULL, false, &BGM_Channel);
}

void CyberAudio::PlaySFX(int _Index)
{
	CoreSystem->playSound(SFX[_Index], NULL, false, &BGM_Channel);
}
