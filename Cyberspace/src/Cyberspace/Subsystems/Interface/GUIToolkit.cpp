#include "GUIToolkit.h"

namespace Cyberspace {
	GUIToolkit* GUIToolkit::Create(const GUIProps& _props)
	{
		return new GUIToolkit(_props);
	}

	GUIToolkit::GUIToolkit(const GUIProps& _props) {
		Init(_props);
	}

	GUIToolkit::~GUIToolkit()
	{
		Terminate();
	}

	void GUIToolkit::Init(const GUIProps& _props)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void GUIToolkit::Configure(EngineWindow* _window)
	{
		ImGui_ImplGlfw_InitForOpenGL(_window->m_Window, true);
	}

	void GUIToolkit::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Test Menu");
		ImGui::Button("Start");
		ImGui::Button("Settings");
		ImGui::Button("Exit");
		ImGui::End();

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
