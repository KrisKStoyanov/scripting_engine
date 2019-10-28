#include "CyberInterface.h"

CyberInterface::CyberInterface(bool& _InitStatus)
{
	_InitStatus = Init();
}

CyberInterface::~CyberInterface()
{
}

bool CyberInterface::Init()
{
	return true;
}

void CyberInterface::Configure()
{
}

void CyberInterface::Process(int _Key, int _Scancode, int _Action, int _Mods)
{
	if (_Key == GLFW_KEY_ESCAPE && _Action == GLFW_PRESS)
	{

	}
}

void CyberInterface::Update()
{
}

void CyberInterface::Terminate()
{
}
