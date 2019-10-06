#include <iostream>
#include <fstream>
#include <algorithm>
#include "CyberEngine.h"

CyberEngine Engine;

int main(int argc, char *argv[]) {

	if (Engine.Init("Cyberspace", 800, 600)) {
		Engine.Start();
	}
	else {
		return -1;
	}

	Engine.Deactivate();

	return 0;
}