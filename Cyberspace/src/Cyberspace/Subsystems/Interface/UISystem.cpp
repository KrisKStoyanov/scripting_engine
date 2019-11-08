#include "UISystem.h"

UISystem::UISystem(bool& _InitStatus)
{
	_InitStatus = Init();
}

UISystem::~UISystem()
{
}

bool UISystem::Init()
{
	return true;
}

void UISystem::Configure()
{
}

void UISystem::Update()
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

void UISystem::Terminate()
{
}
