#include "cspacepch.h"
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

		switch (m_State) {
		case GUIState::StartMenu:
			ImGui::Begin("Main Menu");
			if (_props.m_NetProps.m_ClientState == ClientState::Connected) {
				if (ImGui::Button("Disconnect")) {
					if (_props.m_NetProps.m_ClientState != ClientState::Disconnected) {
						_props.m_NetProps.m_ClientState = ClientState::Disconnecting;
						_BlockingEventQueue.push(new CyberEvent(EventType::DISCONNECT));
					}
				}
			}
			else {
				if (ImGui::Button("Connect")) {
					_props.m_NetProps.m_ClientState = ClientState::Connecting;
					_BlockingEventQueue.push(new CyberEvent(EventType::CONNECT));
				}
			}
			if (ImGui::Button("Start")) {
				m_State = GUIState::Gameplay;
				_props.m_GraphicsProps.m_EnCursor = false;
				_BlockingEventQueue.push(new CyberEvent(EventType::START));
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
			if (ImGui::Button("Video")) {
				m_State = GUIState::VideoSettings;
			}
			if (ImGui::Button("Audio")) {
				m_State = GUIState::AudioSettings;
			}
			if (ImGui::Button("Back")) {
				m_State = GUIState::StartMenu;
			}
			ImGui::End();
			break;
		case GUIState::VideoSettings:
			ImGui::Begin("Video Settings");
			ImGui::SliderFloat("FOV: ", &_props.m_GraphicsProps.m_FOV, 30.0f, 90.0f);
			ImGui::Checkbox("VSync: ", &_props.m_GraphicsProps.m_VSync);
			ImGui::Checkbox("4xMSAA: ", &_props.m_GraphicsProps.m_MSAA);
			ImGui::Checkbox("Fullscreen: ", &_props.m_GraphicsProps.m_Fullscreen);
			if (ImGui::BeginCombo("Resolution: ", _props.m_GraphicsProps.m_DisFormat.DisplayFormat.c_str(), ImGuiComboFlags_NoArrowButton)) {
				for (int i = 0; i < _props.m_GraphicsProps.m_AvDisFormats.size(); ++i) {
					bool is_selected = (
						_props.m_GraphicsProps.m_DisFormat.DisplayFormat == _props.m_GraphicsProps.m_AvDisFormats[i].DisplayFormat);
					if (ImGui::Selectable(_props.m_GraphicsProps.m_AvDisFormats[i].DisplayFormat.c_str(), is_selected)) {
						_props.m_GraphicsProps.m_DisFormat = _props.m_GraphicsProps.m_AvDisFormats[i];
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			if (ImGui::Button("Apply")) {
				_BlockingEventQueue.push(new CyberEvent(EventType::UPDATE_VIDEO_SETTINGS));
			}
			if (ImGui::Button("Revert to Default")) {
				_props.m_GraphicsProps = GraphicsProps();
				_BlockingEventQueue.push(new CyberEvent(EventType::UPDATE_VIDEO_SETTINGS));
			}
			if (ImGui::Button("Back")) {
				m_State = GUIState::Settings;
			}
			ImGui::End();
			break;
		case GUIState::AudioSettings:
			ImGui::Begin("Audio Settings");
			ImGui::SliderFloat("Master Volume: ", &_props.m_AudioProps.MasterVolume, 0.0f, 1.0f);
			ImGui::SliderFloat("Music Volume: ", &_props.m_AudioProps.MusicVolume, 0.0f, 1.0f);
			ImGui::SliderFloat("Sound Volume: ", &_props.m_AudioProps.SoundVolume, 0.0f, 1.0f);
			ImGui::Checkbox("Mute Music: ", &_props.m_AudioProps.MutedBGM);
			ImGui::Checkbox("Mute SFX: ", &_props.m_AudioProps.MutedSFX);

			if (ImGui::Button("Apply")) {
				_BlockingEventQueue.push(new CyberEvent(EventType::UPDATE_AUDIO_SETTINGS));
			}
			if (ImGui::Button("Back")) {
				m_State = GUIState::Settings;
			}
			ImGui::End();
			break;
		case GUIState::Gameplay:
			if (_props.m_GMProps.Paused) {
				if (ImGui::Button("Resume")) {
					_props.m_GraphicsProps.m_EnCursor = false;
					_props.m_GMProps.Paused = false;
					_BlockingEventQueue.push(new CyberEvent(EventType::RESUME));
				}
				if (ImGui::Button("Back to Main Menu")) {
					m_State = GUIState::StartMenu;
				}
			}
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
