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

void CyberInterface::Update()
{
	//if (!_Events.empty()) {

	//		//	for (CyberEvent* Event : PendingEvents) {

	//		//		if (std::find(PendingEvents.begin(), PendingEvents.end(), Event) != PendingEvents.end()) {
	//		//			Engine_Renderer->HandleEvent(Event);
	//		//		}
	//		//		if (std::find(PendingEvents.begin(), PendingEvents.end(), Event) != PendingEvents.end()) {
	//		//			Engine_Physics->HandleEvent(Event);
	//		//		}
	//		//		if (std::find(PendingEvents.begin(), PendingEvents.end(), Event) != PendingEvents.end()) {
	//		//			Engine_Audio->HandleEvent(Event);
	//		//		}
	//		//		if (std::find(PendingEvents.begin(), PendingEvents.end(), Event) != PendingEvents.end()) {
	//		//			Engine_Net->HandleEvent(Event);
	//		//		}
	//		//	}
	//		//}
	//}
}

void CyberInterface::Terminate()
{
}
