#include <iostream>
#include <fstream>
#include <algorithm>
#include "CyberEngine.h"

CyberEngine Engine;

int main(int argc, char *argv[]) {

	if (!Engine.Init("Cyberspace", 800, 600)) {
		return -1;
	}

	return 0;
}