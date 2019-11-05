#include "Renderer.h"

Renderer::Renderer(bool& _InitStatus, int _WindowWidth, int _WindowHeight)
{
	_InitStatus = Init(_WindowWidth, _WindowHeight);
}

Renderer::~Renderer()
{
}

bool Renderer::Init(int _WindowWidth, int _WindowHeight)
{
	glewExperimental = GL_TRUE;
	GLenum initState = glewInit();
	if (initState != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(initState));
		return false;
	}

	glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	MainCamera = new Camera(glm::vec3(-5.0f, 0.0f, 3.0f), 60, _WindowWidth, _WindowHeight);
	MainCamera->SetupShader("./Shaders/BasicVertexShader.glsl", "./Shaders/BasicFragmentShader.glsl", ShaderType::BASIC);
	MainCamera->BasicShader->Activate();

	return true;
}

void Renderer::Draw(GLuint _VAO, GLuint _ElementCount)
{
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _ElementCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::Update(std::queue<CyberEvent*>& _EventQueue, std::vector<Entity*> _EntityCollection, double _CursorPosX, double _CursorPosY, float _DeltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!_EventQueue.empty()) {
		std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::GRAPHICS);
		if (Tag != _EventQueue.front()->Tags.end()) {
			_EventQueue.front()->Tags.erase(Tag);
			switch (_EventQueue.front()->Type) {
			case EventType::MOVE_FORWARD:
				MainCamera->UpdateTransformKeyboard(MovementType::MOVE_FORWARD, _DeltaTime);
				printf("MOVE_FORWARD EVENT\n");
				_EventQueue.pop();
				break;
			case EventType::MOVE_BACKWARD:
				MainCamera->UpdateTransformKeyboard(MovementType::MOVE_BACKWARD, _DeltaTime);
				printf("MOVE_BACKWARD EVENT\n");
				_EventQueue.pop();
				break;
			case EventType::MOVE_LEFT:
				MainCamera->UpdateTransformKeyboard(MovementType::MOVE_LEFT, _DeltaTime);
				printf("MOVE_LEFT EVENT\n");
				_EventQueue.pop();
				break;
			case EventType::MOVE_RIGHT:
				MainCamera->UpdateTransformKeyboard(MovementType::MOVE_RIGHT, _DeltaTime);
				printf("MOVE_RIGHT EVENT\n");
				_EventQueue.pop();
				break;
			default:
				break;
			}
		}
	}
	for (Entity* E : _EntityCollection) {
		if (E->m_Mesh != NULL) {
			E->m_Mesh->ModelMatrix = glm::mat4(1.0f);
			E->m_Mesh->ModelMatrix = glm::translate(E->m_Mesh->ModelMatrix, E->Position);
			E->m_Mesh->ModelMatrix = glm::rotate(E->m_Mesh->ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			Draw(E->m_Mesh->VAO, E->m_Mesh->IndexCollection.size());
			MainCamera->UpdateScene(E->m_Mesh->ModelMatrix);
		}
	}
	MainCamera->UpdateTransformMouse(_CursorPosX, -_CursorPosY);
}

void Renderer::Terminate()
{
	if (MainCamera) {
		if (MainCamera->BasicShader) {
			MainCamera->BasicShader->Clear();
		}
		delete MainCamera;
	}
}

