#include "CyberEngine.h"

CyberEngine::CyberEngine()
{
}

CyberEngine::~CyberEngine()
{
}

bool CyberEngine::Init(std::string _WindowName, unsigned int _WindowWidth, unsigned int _WindowHeight, SDL_RendererFlags _RenderingFlag)
{
	LocalState CurrentState = STARTING;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "WARNING: SDL could not initialize!\n" << std::endl;
		CheckSDLError(__LINE__);
		return 0;
	}

	CR_WindowWidth = _WindowWidth;
	CR_WindowHeight = _WindowHeight;
	CR_MainWindow = SDL_CreateWindow(_WindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CR_WindowWidth, CR_WindowHeight, SDL_WINDOW_OPENGL);
	if (CR_MainWindow == nullptr) {
		std::cout << "WARNING: Window could not be created!\n" << std::endl;
		CheckSDLError(__LINE__);
		return 0;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	// Turn on double buffering with a 24bit Z buffer.
	// May need to change this to 1,16 or 32 based on system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	CR_OGL_Context = SDL_GL_CreateContext(CR_MainWindow);

	glewExperimental = GL_TRUE;
	GLenum initState = glewInit();

	if (initState != GLEW_OK) {
		std::cout << glewGetErrorString(glewInit()) << std::endl;
		return 0;
	}

	// This makes our buffer swap syncronized with the monitor's vertical refresh - Vsync
	if (SDL_GL_SetSwapInterval(1) < 0) {
		std::cout << "WARNING: Vsync could not be set!\n" << std::endl;
		CheckSDLError(__LINE__);
	}

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(CR_MainWindow);
	
	PrintOGLVersion();

	return 1;
}

void CyberEngine::Start()
{
	CR_CurrentState = ACTIVE;
	Update();
}

void CyberEngine::PrintOGLVersion()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "Powered by OpenGL " << value;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "." << value << std::endl;
}

void CyberEngine::CheckSDLError(int line = -1)
{
	std::string ErrorInfo = SDL_GetError();

	if (!ErrorInfo.empty()) {
		std::cout << "SDL Error: " << ErrorInfo << std::endl;

		if (line != -1) {
			std::cout << "\nLine: " << line << std::endl;
		}

		SDL_ClearError();
	}
}

void CyberEngine::Configure()
{
}

void CyberEngine::Update()
{
	while (CR_CurrentState == 1) {
		SDL_Event CurrentEvent;
		while (SDL_PollEvent(&CurrentEvent)) {
			if (CurrentEvent.type == SDL_QUIT) {
				CR_CurrentState = INACTIVE;
				break;
			}
			if (CurrentEvent.type == SDL_KEYDOWN) {
				switch (CurrentEvent.key.keysym.sym) {
				case SDLK_ESCAPE:
					CR_CurrentState = INACTIVE;
					break;
				case SDLK_r:
					glClearColor(1, 0, 0, 1);
					break;
				case SDLK_g:
					glClearColor(0, 1, 0, 1);
					break;
				case SDLK_b:
					glClearColor(0, 0, 1, 1);
					break;
				default:
					break;
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(CR_MainWindow);
	}
}

void CyberEngine::Deactivate()
{
	SDL_GL_DeleteContext(CR_OGL_Context);
	SDL_DestroyWindow(CR_MainWindow);
	SDL_Quit();
}
