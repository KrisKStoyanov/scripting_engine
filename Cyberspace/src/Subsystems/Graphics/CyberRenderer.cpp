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
	
	glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	MainCamera = new Camera(glm::vec3(-5.0f,0.0f,3.0f), 60, _WindowWidth, _WindowHeight);
	MainCamera->SetupShader("./Shaders/BasicVertexShader.glsl", "./Shaders/BasicFragmentShader.glsl", ShaderType::BASIC);
	MainCamera->BasicShader->Activate();

	return true;
}

void CyberRenderer::Draw(GLuint _VAO, GLuint _ElementCount)
{
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _ElementCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
	
void CyberRenderer::Update(std::queue<CyberEvent*>& _EventQueue, std::vector<Entity*> _EntityCollection, double _CursorPosX, double _CursorPosY, float _DeltaTime)
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
		if (E->GFX_Comp != NULL) {
			E->GFX_Comp->ModelMatrix = glm::mat4(1.0f);
			E->GFX_Comp->ModelMatrix = glm::translate(E->GFX_Comp->ModelMatrix, E->Position);
			E->GFX_Comp->ModelMatrix = glm::rotate(E->GFX_Comp->ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			MainCamera->UpdateScene(E->GFX_Comp->ModelMatrix);
			Draw(E->GFX_Comp->VAO, E->GFX_Comp->IndexCollection.size());
		}
	}
	MainCamera->UpdateTransformMouse(_CursorPosX, -_CursorPosY);
}

void CyberRenderer::Terminate()
{
	if (MainCamera) {
		if (MainCamera->BasicShader) {
			MainCamera->BasicShader->Clear();
		}
		delete MainCamera;
	}
}

