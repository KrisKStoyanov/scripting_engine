#include "Camera.h"

Camera::Camera(glm::vec3 _Position, float _FOV, float _ProjWidth, float _ProjHeight)
{
	Position = _Position;
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Direction = glm::normalize(Position);
	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::normalize(glm::cross(WorldUp, Direction));
	Up = glm::cross(Direction, Right);

	MovementSpeed = 5.f;
	MouseSensitivity = 0.05f;

	ViewMatrix = glm::lookAt(Position, Position + Front, Up);
	ProjectionMatrix = glm::perspective(glm::radians(_FOV), _ProjWidth * (1.f / _ProjHeight), 0.1f, 1000.0f);
}

Camera::~Camera()
{
}

void Camera::UpdateTransformKeyboard(MovementType _Type, float _DeltaTime)
{
	switch (_Type) {
	case MovementType::MOVE_FORWARD:
		Position += Front * MovementSpeed * _DeltaTime;
		break;
	case MovementType::MOVE_BACKWARD:
		Position += -Front * MovementSpeed * _DeltaTime;
		break;
	case MovementType::MOVE_LEFT:
		Position += -glm::normalize(glm::cross(Front, Up)) * MovementSpeed * _DeltaTime;
		break;
	case MovementType::MOVE_RIGHT:
		Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed * _DeltaTime;
		break;
	default:
		break;
	}
	ViewMatrix = glm::lookAt(Position, Position + Front, Up);
}

void Camera::UpdateTransformMouse(GLfloat _CursorX, GLfloat _CursorY)
{
	if (FirstMouse) {
		LastMousePosX = _CursorX;
		LastMousePosY = _CursorY;
		FirstMouse = false;
	}

	float OffsetX = _CursorX - LastMousePosX;
	float OffsetY = _CursorY - LastMousePosY;

	LastMousePosX = _CursorX;
	LastMousePosY = _CursorY;

	OffsetX *= MouseSensitivity;
	OffsetY *= MouseSensitivity;

	Yaw += OffsetX;
	Pitch += OffsetY;

	Pitch = Pitch > 90.f ? 90.f : Pitch;
	Pitch = Pitch < -90.f ? -90.f : Pitch;

	glm::vec3 UpdatedFrontDir;
	UpdatedFrontDir.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	UpdatedFrontDir.y = sin(glm::radians(Pitch));
	UpdatedFrontDir.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(UpdatedFrontDir);
	ViewMatrix = glm::lookAt(Position, Position + Front, Up);
}

