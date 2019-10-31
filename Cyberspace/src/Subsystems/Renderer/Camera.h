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

class Camera
{
public:
	Camera(glm::vec3 _Position = glm::vec3(0.0f, 0.0f, 0.0f));
	~Camera();

	glm::vec3 Position, Direction, Target, Front, Up, Right, WorldUp;
	GLfloat Yaw, Pitch, MovementSpeed, MouseSensitivIty;
	glm::mat4 View, Projection;

	GLuint ViewMatrixLoc, ProjectionMatrixLoc;

	void UpdateCameraVectors();
};

