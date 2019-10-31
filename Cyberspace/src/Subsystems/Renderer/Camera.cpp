#include "Camera.h"

Camera::Camera(glm::vec3 _Position)
{
	Position = _Position;
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Direction = glm::normalize(Position - Target);	

	WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::normalize(glm::cross(WorldUp, Direction));

	Up = glm::cross(Direction, Right);

	View = glm::lookAt(Position, Position + Front, Up);
}

Camera::~Camera()
{
}

void Camera::UpdateCameraVectors()
{
}
