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
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//ImGui::StyleColorsDark();
		//ImGui_ImplOpenGL3_Init("#version 450");
		//ImGui::CreateContext();
		//ImGuiIO& IO = ImGui::GetIO();
		//int AtlasWidth, AtlasHeight;
		//unsigned char* AtlasPixels = NULL;
		//IO.Fonts->GetTexDataAsRGBA32(&AtlasPixels, &AtlasWidth, &AtlasHeight); 

		//ImGui::StyleColorsDark();
	}

	void UISystem::Setup(EngineWindow* _window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 450");
		ImGui_ImplGlfw_InitForOpenGL(_window->MainWindow, true);
	}

	void UISystem::Configure()
	{
	}

	void UISystem::OnUpdate(std::queue<CyberEvent*>& _eventQueue)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hi World!");
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UISystem::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

}

