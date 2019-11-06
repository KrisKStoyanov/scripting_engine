#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

enum class MovementType {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT
};

class Camera
{
public:
	Camera(glm::vec3 _Position, float _FOV, float _ProjWidth, float _ProjHeight);
	~Camera();

	glm::vec3 Position, Direction, Target, Front, Up, Right, WorldUp;
	GLfloat Yaw, Pitch, MovementSpeed, MouseSensitivIty;
	glm::mat4 ViewMatrix, ProjectionMatrix;

	float MouseSensitivity;

	void UpdateTransformKeyboard(MovementType _Type, float _DeltaTime);
	void UpdateTransformMouse(GLfloat _CursorX, GLfloat _CursorY);

	float LastMousePosX;
	float LastMousePosY;
	bool FirstMouse = true;
};

