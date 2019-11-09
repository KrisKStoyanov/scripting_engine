#include <cstdio>
#include <string>

#include <enet/enet.h>
#include <iostream>

ENetAddress address;
ENetHost* server;
bool running = true;

int main(int argc, char** argv) {
	//Init ENet:
	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occured while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	//Create server:
	address.host = ENET_HOST_ANY;
	address.port = 1234;
	server = enet_host_create(&address, 2, 2, 0, 0);
	if (server == NULL) {
		fprintf(stderr, "An error occured while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
	printf("Server is running...\n");
	std::string netEventData = "Client Info";
	while (running) {
		ENetEvent netEvent;
		while (enet_host_service(server, &netEvent, 0) > 0) {
			switch (netEvent.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n",
					netEvent.peer->address.host,
					netEvent.peer->address.port);
				netEvent.peer->data = &netEventData;
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet of length %u containing %s was received  from %s on channel %u.\n",
					netEvent.packet->dataLength,
					netEvent.packet->data,
					netEvent.peer->data,
					netEvent.channelID);
				enet_packet_destroy(netEvent.packet);

				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", netEvent.peer->data);
				
				netEvent.peer->data = NULL;
				//Check if peer is still connected and force disconnect
			}
		}
	}

	enet_host_destroy(server);
}