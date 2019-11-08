#pragma once

#ifdef CSPACE_PLATFORM_WINDOWS

extern Cyberspace::Application* Cyberspace::CreateApplication();

int main(int argc, char** argv) {
	Cyberspace::Log::Init();

	auto app = Cyberspace::CreateApplication();
	app->Run();
	delete app;
}

#endif