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

enum class ShaderType {
	BASIC = 0,
	SKYBOX = 1
};

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

	void SetupShader(const GLchar* _VertexShaderPath, const GLchar* _FragmentShaderPath, ShaderType _Type);
	Shader* BasicShader = NULL;
	Shader* SkyboxShader = NULL;

	glm::vec3 Position, Direction, Target, Front, Up, Right, WorldUp;
	GLfloat Yaw, Pitch, MovementSpeed, MouseSensitivIty;
	glm::mat4 ViewMatrix, ProjectionMatrix;

	GLuint ProjectionMatrixLoc, ViewMatrixLoc, ModelMatrixLoc;

	float MouseSensitivity;

	void UpdateScene(glm::mat4 _ModelMatrix);
	void UpdateTransformKeyboard(MovementType _Type, float _DeltaTime);
	void UpdateTransformMouse(GLfloat _CursorX, GLfloat _CursorY);

	float LastMousePosX;
	float LastMousePosY;
	bool FirstMouse = true;
};

