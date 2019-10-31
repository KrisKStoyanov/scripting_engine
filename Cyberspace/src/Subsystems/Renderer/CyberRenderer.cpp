#include "CyberRenderer.h"

CyberRenderer::CyberRenderer(bool& _InitStatus, int _WindowWidth, int _WindowHeight)
{
	_InitStatus = Init(_WindowWidth, _WindowHeight);
}

CyberRenderer::~CyberRenderer()
{
}

bool CyberRenderer::Init(int _WindowWidth, int _WindowHeight)
{
	glewExperimental = GL_TRUE;
	GLenum initState = glewInit();

	if (initState != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(initState));
		return false;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	MainCamera = new Camera(glm::vec3(0.0f,0.0f,3.0f));
	//MainCamera->View = glm::mat4(1.0f);
	//MainCamera->View = glm::translate(MainCamera->View, glm::vec3(0.0f, 0.0f, -3.0f));
	MainCamera->Projection = glm::perspective(glm::radians(45.0f), (float)(_WindowWidth * (1.f / _WindowHeight)), 0.1f, 1000.0f);

	Configure();
	return true;
}

void CyberRenderer::Configure()
{
	Shader* TestShader = new Shader("./Shaders/vert.glsl", "./Shaders/frag.glsl");
	CR_Shaders["TestShader"] = TestShader;
}
	
void CyberRenderer::Update(std::queue<CyberEvent*>& _EventQueue, std::vector<Entity*> _EntityCollection)
{
	if (!_EventQueue.empty()) {
		std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::GRAPHICS);
		if (Tag != _EventQueue.front()->Tags.end()) {
			_EventQueue.front()->Tags.erase(Tag);
			switch (_EventQueue.front()->Type) {
			case EventType::MOVE_FORWARD:
				TestEntity->Position += glm::vec3(0, 0.001f, 0);
				printf("MOVE_FORWARD EVENT\n");
				break;
			case EventType::MOVE_BACKWARD:
				TestEntity->Position += glm::vec3(0, -0.001f, 0);
				printf("MOVE_BACKWARD EVENT\n");
				break;
			case EventType::MOVE_LEFT:
				TestEntity->Position += glm::vec3(-0.001f, 0, 0);
				printf("MOVE_LEFT EVENT\n");
				break;
			case EventType::MOVE_RIGHT:
				TestEntity->Position += glm::vec3(0.001f, 0, 0);
				printf("MOVE_RIGHT EVENT\n");
				break;
			default:
				break;
			}
			if (_EventQueue.front()->Tags.empty()) {
				_EventQueue.pop();
			}
		}
	}
	for (Entity* E : _EntityCollection) {
		if (E->GFX_Comp != NULL) {
			E->GFX_Comp->ModelMatrix = glm::mat4(1.0f);
			E->GFX_Comp->ModelMatrix = glm::translate(E->GFX_Comp->ModelMatrix, E->Position);
			E->GFX_Comp->ModelMatrixLoc = glGetUniformLocation(CR_Shaders["TestShader"]->ProgramID, "Model");
			E->GFX_Comp->ModelMatrix = glm::rotate(E->GFX_Comp->ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			MainCamera->ViewMatrixLoc = glGetUniformLocation(CR_Shaders["TestShader"]->ProgramID, "View");
			MainCamera->ProjectionMatrixLoc = glGetUniformLocation(CR_Shaders["TestShader"]->ProgramID, "Projection");
			CR_Shaders["TestShader"]->Activate();
			glUniformMatrix4fv(E->GFX_Comp->ModelMatrixLoc, 1, GL_FALSE, glm::value_ptr(E->GFX_Comp->ModelMatrix));
			glUniformMatrix4fv(MainCamera->ViewMatrixLoc, 1, GL_FALSE, glm::value_ptr(MainCamera->View));
			glUniformMatrix4fv(MainCamera->ProjectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(MainCamera->Projection));
			glBindVertexArray(E->GFX_Comp->VAO);
			glDrawElements(GL_TRIANGLES, E->GFX_Comp->IndexCollection.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			CR_Shaders["TestShader"]->Deactivate();
		}
	}
}

//void CyberRenderer::HandleEvent(CyberEvent* _Event)
//{
//	if (_Type == EventType::MOVE_FORWARD) {
//		TestEntity->Position += glm::vec3(0, 0.001f, 0);
//		//main character vehicle move forward
//	}
//	if (_Type == EventType::MOVE_BACKWARD) {
//		TestEntity->Position += glm::vec3(0, -0.001f, 0);
//		//main character vehicle move backward
//	}
//	if (_Type == EventType::MOVE_LEFT) {
//		TestEntity->Position += glm::vec3(-0.001f, 0, 0);
//		//main character vehicle move left
//	}
//	if (_Type == EventType::MOVE_RIGHT) {
//		TestEntity->Position += glm::vec3(0.001f, 0, 0);
//		//main character vehicle move right
//	}
//	if (_Event->Tags.size == 1) {
//		
//	}
//}

void CyberRenderer::Terminate()
{
	for (std::pair<std::string, Shader*> S : CR_Shaders) {
		S.second->Clear();
	}
}

void CyberRenderer::AddShader(std::string _ShaderKey, Shader* _TargetShader)
{
	CR_Shaders[_ShaderKey] = _TargetShader;
}

void CyberRenderer::PrintProgramLog(GLuint _ProgramID)
{
	if (glIsProgram(_ProgramID)) {
		int InfoLogLength = 0;
		int MaxLength = InfoLogLength;

		glGetProgramiv(_ProgramID, GL_INFO_LOG_LENGTH, &MaxLength);

		char* InfoLog = new char[MaxLength];

		glGetProgramInfoLog(_ProgramID, MaxLength, &InfoLogLength, InfoLog);
		if (InfoLogLength > 0) {
			fprintf(stdout, "%s\n", InfoLog);
		}

		delete[] InfoLog;
	}
	else {
		fprintf(stdout, "%d is not a valid program ID\n", _ProgramID);
	}
}

void CyberRenderer::PrintShaderLog(GLuint _ShaderID)
{
	if (glIsShader(_ShaderID)) {
		int InfoLogLength = 0;
		int MaxLength = InfoLogLength;

		glGetShaderiv(_ShaderID, GL_INFO_LOG_LENGTH, &MaxLength);

		char* InfoLog = new char[MaxLength];

		glGetShaderInfoLog(_ShaderID, MaxLength, &InfoLogLength, InfoLog);
		if (InfoLogLength > 0) {
			fprintf(stdout, "%s\n", InfoLog);
		}

		delete[] InfoLog;
	}
	else {
		fprintf(stdout, "%d is not a valid shader ID\n", _ShaderID);
	}
}
