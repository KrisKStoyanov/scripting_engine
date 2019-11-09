#pragma once

#ifdef CSPACE_PLATFORM_WINDOWS

extern Cyberspace::Application* Cyberspace::CreateApplication();

int main(int argc, char** argv) {
	Cyberspace::Log::Init();
	CSPACE_CORE_INFO("Initialized Engine Logs!");
	CSPACE_CLIENT_TRACE("Initialized Game Logs!");
	auto app = Cyberspace::CreateApplication();
	app->Run();
	delete app;
}

#endif