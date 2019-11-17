#include "GUIToolkit.h"

namespace Cyberspace {
	GUIToolkit* GUIToolkit::Create(EngineWindow* _window, const GraphicsProps& _props)
	{
		return new GUIToolkit(_window, _props);
	}

	GUIToolkit::GUIToolkit(EngineWindow* _window, const GraphicsProps& _props) {
		Init(_window, _props);
	}

	GUIToolkit::~GUIToolkit()
	{
		Terminate();
	}

	void GUIToolkit::Init(EngineWindow* _window, const GraphicsProps& _props)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 450");
		ImGui_ImplGlfw_InitForOpenGL(_window->GetNativeWindow(), true);
	}

	void GUIToolkit::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, EngineProps& _props)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(&showDemo);
		switch (m_State) {
		case GUIState::StartMenu:
			ImGui::Begin("Main Menu");
			if (ImGui::Button("Start")) {
				m_State = GUIState::Gameplay;
				_BlockingEventQueue.push(new CyberEvent(EventType::TOGGLE_CAMERA_MOVEMENT, EventTag::GRAPHICS, EventTag::WINDOW));
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
			ImGui::SliderFloat("FOV: ", &_props.m_GraphicsProps.m_FOV, 30.0f, 90.0f);
			ImGui::Checkbox("VSync: ", &_props.m_GraphicsProps.m_VSync);
			ImGui::Checkbox("4xMSAA: ", &_props.m_GraphicsProps.m_MSAA);
			ImGui::Checkbox("Fullscreen: ", &_props.m_GraphicsProps.m_Fullscreen);
			if (ImGui::BeginCombo("Resolution: ", m_CurrentRes, ImGuiComboFlags_NoArrowButton)) {
				for (int i = 0; i < IM_ARRAYSIZE(m_Resolutions); ++i) {
					bool is_selected = (m_CurrentRes == m_Resolutions[i]);
					if (ImGui::Selectable(m_Resolutions[i], is_selected)) {
						m_CurrentRes = m_Resolutions[i];
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			if (ImGui::Button("Apply")) {
				_BlockingEventQueue.push(new CyberEvent(EventType::UPDATE_SETTINGS));
			}
			if (ImGui::Button("Revert to Default")) {
				_props.m_GraphicsProps = GraphicsProps();
				_BlockingEventQueue.push(new CyberEvent(EventType::UPDATE_SETTINGS));
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
