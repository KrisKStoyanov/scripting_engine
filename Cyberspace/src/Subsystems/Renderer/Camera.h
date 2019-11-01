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

class Camera
{
public:
	Camera(glm::vec3 _Position, float _FOV, float _ProjWidth, float _ProjHeight);
	~Camera();

	void SetupShader(const GLchar* _VertexShaderPath, const GLchar* _FragmentShaderPath);
	Shader* MainShader = NULL;

	glm::vec3 Position, Direction, Target, Front, Up, Right, WorldUp;
	GLfloat Yaw, Pitch, MovementSpeed, MouseSensitivIty;
	glm::mat4 ViewMatrix, ProjectionMatrix;

	GLuint ProjectionMatrixLoc, ViewMatrixLoc, ModelMatrixLoc;

	void Update(glm::mat4 _ModelMatrix);
	void UpdateCameraVectors();
};

