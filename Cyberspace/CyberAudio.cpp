#include "CyberAudio.h"

CyberAudio::CyberAudio()
{

}

CyberAudio::~CyberAudio()
{
}

bool CyberAudio::Activate()
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
	//EventResult = FMOD::Studio::System::create(&HighLevelSystem);
	//if (EventResult != FMOD_OK) {
	//	printf("FMOD Error!\n(%d)\n", EventResult);
	//}
	//if (HighLevelSystem) {
	//	printf("High-level audio system created\n");
	//	EventResult = HighLevelSystem->getCoreSystem(&LowLevelSystem);
	//}
	//if (EventResult != FMOD_OK) {
	//	printf("FMOD Error!\n(%d)\n", EventResult);
	//}
	Configure();
	return true;
}

void CyberAudio::Configure()
{
	CoreSystem->createSound("../External Resources/Audio/TitleScreenTrack.wav", FMOD_LOOP_OFF, NULL, &BGM[0]);
	if (BGM[0] != NULL) {
		printf("Title screen track loaded\n");
		BGM[0]->setDefaults(16400, 0);
	}
}

void CyberAudio::Update()
{
	
}

void CyberAudio::Deactivate()
{
}

void CyberAudio::PlayBGM(int _Index)
{
	CoreSystem->playSound(BGM[_Index], NULL, false, &BGM_Channel);
}

void CyberAudio::PlaySFX(int _Index)
{
	CoreSystem->playSound(SFX[_Index], NULL, false, &BGM_Channel);
}
