#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fmod.hpp>
#include <fmod_studio.hpp>

#include "../../Entity.h"
#include "../../CyberEvent.h"

class CyberAudio
{
public:
	CyberAudio(bool& _InitStatus);
	~CyberAudio();
	bool Init();
	void Update(std::vector<Entity*> _EntityCollection);
	void HandleEvent(CyberEvent* _Event);
	void Terminate();
	void PlayBGM(int _Index);
	void PlaySFX(int _Index);

	//FMOD::Studio::System* HighLevelSystem = NULL;
	//FMOD::System* LowLevelSystem = NULL;
	FMOD::System *CoreSystem = NULL;
	FMOD::Sound* BGM[2];
	FMOD::Sound* SFX[2];
	//std::vector<FMOD::Sound*> BGM;
	//std::vector<FMOD::Sound*> SFX;

	FMOD::Channel* BGM_Channel = NULL;
	FMOD::Channel* SFX_Channel = NULL;
};

