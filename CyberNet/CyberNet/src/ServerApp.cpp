#include "GameServer.h"

int main(int argc, char** argv) {
	GameServer* server = new GameServer();
	server->Init();
	server->CreateServer();
	server->OnUpdate();
	server->Terminate();
}