#pragma once

//Exclusive platform implementation
#ifdef CSPACE_PLATFORM_WINDOWS

//Obtain a local reference to the CreateApplication function declared in the Sandbox project
extern Cyberspace::Application* Cyberspace::CreateApplication();

//Main entry point of the application
int main(int argc, char** argv) {
	//Initialize logging functionality:
	Cyberspace::Log::Init();
	//Test Engine-centric (Core) logs:
	CSPACE_CORE_INFO("Initialized Engine Logs!");
	//Test Game-centric (Client/Application) logs:
	CSPACE_CLIENT_TRACE("Initialized Game Logs!");
	//Create application in memory using the obtain function reference
	Cyberspace::Application* app = Cyberspace::CreateApplication();
	//Run the application
	app->Run();
	//Release allocated memory associated with the application
	delete app;
}

#endif