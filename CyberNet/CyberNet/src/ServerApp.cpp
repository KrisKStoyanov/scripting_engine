#include "GameServer.h"

int main(int argc, char** argv) {
	GameServer* server = GameServer::Create();
	server->Init();
	server->CreateServer();
	server->OnUpdate();
	server->Terminate();
}