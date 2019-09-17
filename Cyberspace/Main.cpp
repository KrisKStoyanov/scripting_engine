#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm-0.9.6.3/glm/glm.hpp>
#include <glm-0.9.6.3/glm/matrix.hpp>
#include <glm-0.9.6.3/glm/gtc/type_ptr.hpp>

int main(int argc, char *argv[]) {

	glm::vec3 v1(1, 2, 3);
	glm::vec3 v2(3, 4, 5);

	glm::vec3 v3 = v1 + v2;

	glm::vec3** image;

	std::cout << "v1 " << "[" << v1.x << " " << v1.y << " " << v1.z << "]" << std::endl;
	std::cout << "v2 " << "[" << v2.x << " " << v2.y << " " << v2.z << "]" << std::endl;
	std::cout << "v3 " << "[" << v3.x << " " << v3.y << " " << v3.z << "]" << std::endl;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("Cyberspace", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
		return -1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum initState = glewInit();

	if (initState != GLEW_OK) {
		std::cout << glewGetErrorString(glewInit()) << std::endl;
	}
	
	while (true) 
	{
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					exit(0);
					break;
				}
				break;
			}
		}
		
		Uint8 redVal = rand() % 255;
		Uint8 greenVal = rand() % 255;
		Uint8 blueVal = rand() % 255;

		SDL_SetRenderDrawColor(renderer, redVal, greenVal, blueVal, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}