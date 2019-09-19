#include <iostream>
#include <fstream>
#include <algorithm>
#include "CyberEngine.h"

CyberEngine Engine;

int main(int argc, char *argv[]) {

	if (Engine.Init("Cyberspace", 800, 600, SDL_RENDERER_ACCELERATED)) {
		Engine.Start();
	}
	else {
		return -1;
	}

	Engine.Deactivate();

	return 0;
}