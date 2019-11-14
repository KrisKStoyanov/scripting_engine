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
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 450");
		//ImGui::CreateContext();
		//ImGuiIO& IO = ImGui::GetIO();
		//int AtlasWidth, AtlasHeight;
		//unsigned char* AtlasPixels = NULL;
		//IO.Fonts->GetTexDataAsRGBA32(&AtlasPixels, &AtlasWidth, &AtlasHeight); 

		//ImGui::StyleColorsDark();
	}

	void UISystem::Setup(EngineWindow* _window)
	{
		ImGui_ImplGlfw_InitForOpenGL(_window->MainWindow, true);
	}

	void UISystem::Configure()
	{
	}

	void UISystem::OnUpdate(EngineWindow* _window, std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//float time = (float)glfwGetTime();
		//io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		//m_Time = time;

		if (m_ShowStartMenu) {
			ImGui::Begin("Main Menu");
			
			if (ImGui::Button("Start")) {
				m_StartGame = !m_StartGame;
				m_ShowStartMenu = !m_ShowStartMenu;
			}
			
			if (ImGui::Button("Options")) {
				m_ShowOptionsMenu = !m_ShowOptionsMenu;
				m_ShowStartMenu = !m_ShowStartMenu;
			}

			if (ImGui::Button("Exit")) {
				_BlockingEventQueue.push(new CyberEvent(EventType::EXIT));
			}

			ImGui::End();
		}

		if (m_ShowOptionsMenu) {
			ImGui::Begin("Options");

			//ImGui::InputInt("Resolution X", &_window->m_WindowWidth);
			//ImGui::InputInt("Resolution Y", &_window->m_WindowHeight);
			//ImGui::Checkbox("VSync", &_window->m_VSync);

			if (ImGui::Button("Back")) {
				m_ShowOptionsMenu = !m_ShowOptionsMenu;
				m_ShowStartMenu = !m_ShowStartMenu;
			}

			ImGui::End();
		}
		
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

