#include "UISystem.h"

namespace Cyberspace {
	UISystem* Cyberspace::UISystem::Create(const UIProps& _props)
	{
		return new UISystem(_props);
	}

	Cyberspace::UISystem::UISystem(const UIProps& _props)
	{
		Init(_props);
	}

	UISystem::~UISystem()
	{
		Terminate();
	}

	void UISystem::Init(const UIProps& _props)
	{

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

}

