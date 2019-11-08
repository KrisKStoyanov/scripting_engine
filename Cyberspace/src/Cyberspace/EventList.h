#pragma once
#include "CyberEvent.h"
#include <string>
#include <iostream>

inline void MoveForwardEvent(EventType _Type) {
	printf("EVENT: Move Forward\n");
};

inline void MoveBackwardEvent(EventType _Type) {
	printf("EVENT: Move Backward\n");
};

inline void MoveLeftEvent(EventType _Type) {
	printf("EVENT: Move Left\n");
};

inline void MoveRightEvent(EventType _Type) {
	printf("EVENT: Move Right\n");
};

inline void Exit(EventType _Type) {
	printf("EVENT: Exit ;(\n");
};
