#include "GUIToolkit.h"

namespace Cyberspace {
	GUIToolkit* GUIToolkit::Create(EngineWindow*& _window, const GUIProps& _props)
	{
		return new GUIToolkit(_window, _props);
	}

	GUIToolkit::GUIToolkit(EngineWindow*& _window, const GUIProps& _props) {
		Init(_window, _props);
	}

	GUIToolkit::~GUIToolkit()
	{
		Terminate();
	}

	void GUIToolkit::Init(EngineWindow*& _window, const GUIProps& _props)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 450");
		Configure(_window);
	}

	void GUIToolkit::Configure(EngineWindow*& _window)
	{
		ImGui_ImplGlfw_InitForOpenGL(_window->GetNativeWindow(), true);
	}

	void GUIToolkit::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, GraphicsProps& _props)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		switch (m_State) {
		case GUIState::StartMenu:
			ImGui::Begin("Main Menu");
			if (ImGui::Button("Start")) {
				m_State = GUIState::Gameplay;
			}
			if (ImGui::Button("Settings")) {
				m_State = GUIState::Settings;
			}
			if (ImGui::Button("Exit")) {
				_BlockingEventQueue.push(new CyberEvent(EventType::EXIT));
			}
			ImGui::End();
			break;
		case GUIState::Settings:
			ImGui::Begin("Settings");
			ImGui::SliderFloat("FOV: ", &_props.FOV, 30.0f, 90.0f);
			ImGui::Checkbox("VSync: ", &_props.windowProps.VSync);
			ImGui::SliderInt("ResX: ", &_props.windowProps.Width, 800.0f, 1280.0f);
			ImGui::SliderInt("ResY: ", &_props.windowProps.Height, 600.0f, 720.0f);
			if (ImGui::Button("Apply")) {
				_BlockingEventQueue.push(new CyberEvent(EventType::UPDATE_SETTINGS, EventTag::GRAPHICS));
			}
			if (ImGui::Button("Back")) {
				m_State = GUIState::StartMenu;
			}
			ImGui::End();
			break;
		case GUIState::Gameplay:
			ImGui::Begin("Gameplay");
			if (ImGui::Button("Pause")) {
				m_State = GUIState::PauseMenu;
			}
			ImGui::End();
			break;
		case GUIState::PauseMenu:
			ImGui::Begin("Pause Menu");
			if (ImGui::Button("Resume")) {
				m_State = GUIState::Gameplay;
			}
			if (ImGui::Button("Back to Main Menu")) {
				m_State = GUIState::StartMenu;
			}
			ImGui::End();
			break;
		default:
			break;
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUIToolkit::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
