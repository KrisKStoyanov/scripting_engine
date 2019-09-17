#include <iostream>
#include <fstream>
#include <algorithm>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int WIDTH = 640;
const unsigned int HEIGHT = 480;

glm::vec3 image[WIDTH][HEIGHT];
glm::vec3** image2;

int main(int argc, char *argv[]) {

	//image2 = new glm::vec3 * [WIDTH];
	//for (int i = 0; i < WIDTH; ++i) {
	//	image2[i] = new glm::vec3 [HEIGHT];
	//}

	//for (int x = 0; x < WIDTH; ++x) {
	//	for (int y = 0; y < HEIGHT; ++y) {
	//		image2[x][y] = glm::vec3(1, 0, 1);
	//	}
	//}

	//std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	//ofs << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
	//for (unsigned y = 0; y < HEIGHT; ++y)
	//{
	//	for (unsigned x = 0; x < WIDTH; ++x)
	//	{
	//		ofs << (unsigned char)(std::min((float)1, (float)image2[x][y].x) * 255) <<
	//			(unsigned char)(std::min((float)1, (float)image2[x][y].y) * 255) <<
	//			(unsigned char)(std::min((float)1, (float)image2[x][y].z) * 255);
	//	}
	//}
	//ofs.close();

	int PixelNormalizedx;
	int PixelNormalizedy;

	//for (int x = 0; x < WIDTH; ++x) {
	//	for (int y = 0; y < HEIGHT; ++y) {
	//		glm::vec3 ray = new glm::vec3 
	//	}
	//}

	for (int i = 0; i < WIDTH; ++i) {
		for (int y = 0; y < HEIGHT; ++y) {
			
		}
	}

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

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}