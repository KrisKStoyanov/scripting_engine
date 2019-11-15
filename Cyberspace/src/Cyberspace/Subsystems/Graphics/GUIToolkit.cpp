#include "GUIToolkit.h"

namespace Cyberspace {
	GUIToolkit* GUIToolkit::Create(EngineWindow* _window, const GUIProps& _props)
	{
		return new GUIToolkit(_window, _props);
	}

	GUIToolkit::GUIToolkit(EngineWindow* _window, const GUIProps& _props) {
		Init(_window, _props);
	}

	GUIToolkit::~GUIToolkit()
	{
		Terminate();
	}

	void GUIToolkit::Init(EngineWindow* _window, const GUIProps& _props)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 450");
		Configure(_window);
	}

	void GUIToolkit::Configure(EngineWindow* _window)
	{
		ImGui_ImplGlfw_InitForOpenGL(_window->GetNativeWindow(), true);
	}

	void GUIToolkit::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		switch (CurrentState) {
		case StartMenu:
			ImGui::Begin("Main Menu");
			ImGui::Button("Start");
			ImGui::Button("Settings");
			ImGui::Button("Exit");
			ImGui::End();
			break;
		case Gameplay:
			ImGui::Begin("Gameplay");
			ImGui::Button("Pause");
			ImGui::End();
			break;
		case PauseMenu:
			ImGui::Begin("Pause Menu");
			ImGui::Button("Resume");
			ImGui::Button("Settings");
			ImGui::Button("Back to Main Menu");
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
