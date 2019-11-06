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

	MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), 60, _WindowWidth, _WindowHeight);
	TextureShader = SetupShader("./Shaders/TextureVertexShader.glsl", "./Shaders/TextureFragmentShader.glsl", ShaderType::TEXTURE);

	return true;
}

void Renderer::Draw(Camera* _Camera, Entity* _Entity, Shader* _Shader)
{
	if (_Entity->m_Model) {
		_Shader->Activate();

		for (int i = 0; i < _Entity->m_Model->Meshes.size(); ++i) {
			_Entity->m_Model->ModelMatrix = glm::mat4(1.0f);
			_Entity->m_Model->ModelMatrix = glm::translate(_Entity->m_Model->ModelMatrix, _Entity->Position);
			//_Entity->m_Model->ModelMatrix = glm::rotate(_Entity->m_Model->ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			
			_Shader->Update(_Entity->m_Model->ModelMatrix, _Camera->ViewMatrix, _Camera->ProjectionMatrix);
			glBindVertexArray(_Entity->m_Model->Meshes[i].VAO);
			glDrawElements(GL_TRIANGLES, _Entity->m_Model->Meshes[i].IndexCollection.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		_Shader->Deactivate();
	}
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
				MainCamera->UpdateTransformKeyboard(MovementType::FORWARD, _DeltaTime);
				printf("MOVE_FORWARD EVENT\n");
				_EventQueue.pop();
				break;
			case EventType::MOVE_BACKWARD:
				MainCamera->UpdateTransformKeyboard(MovementType::BACKWARD, _DeltaTime);
				printf("MOVE_BACKWARD EVENT\n");
				_EventQueue.pop();
				break;
			case EventType::MOVE_LEFT:
				MainCamera->UpdateTransformKeyboard(MovementType::LEFT, _DeltaTime);
				printf("MOVE_LEFT EVENT\n");
				_EventQueue.pop();
				break;
			case EventType::MOVE_RIGHT:
				MainCamera->UpdateTransformKeyboard(MovementType::RIGHT, _DeltaTime);
				printf("MOVE_RIGHT EVENT\n");
				_EventQueue.pop();
				break;
			default:
				break;
			}
		}
	}
	for (Entity* E : _EntityCollection) {
		Draw(MainCamera, E, TextureShader);
	}
	MainCamera->UpdateTransformMouse(_CursorPosX, -_CursorPosY);
}

void Renderer::Terminate()
{
	if (BasicShader) {
		BasicShader->Clear();
		delete BasicShader;
	}
	if (TextureShader) {
		TextureShader->Clear();
		delete TextureShader;
	}
	if (SkyboxShader) {
		SkyboxShader->Clear();
		delete SkyboxShader;
	}
	if (MainCamera) {
		delete MainCamera;
	}
}

Shader* Renderer::SetupShader(const GLchar* _VertexShaderPath, const GLchar* _FragmentShaderPath, ShaderType _Type)
{
	Shader* TempShader = new Shader(_VertexShaderPath, _FragmentShaderPath);
	if (TempShader == NULL) {
		printf("Failed to create shader!\nVertex shader filepath:%s\nFragment shader filepath:%s\n",_VertexShaderPath, _FragmentShaderPath);
		return NULL;
	}
	return TempShader;
}