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
	Setup(_WindowWidth, _WindowHeight);
	return true;
}

void Renderer::Setup(int _WindowWidth, int _WindowHeight)
{
	MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), 60, _WindowWidth, _WindowHeight);
	TextureShader = SetupShader("./Shaders/TextureVertexShader.glsl", "./Shaders/TextureFragmentShader.glsl", ShaderType::TEXTURE);
	std::vector<std::string> SkyboxCubemapFaces
	{
		"../External Resources/3D/Skybox/miramar_ft.tga",
		"../External Resources/3D/Skybox/miramar_bk.tga",
		"../External Resources/3D/Skybox/miramar_up.tga",
		"../External Resources/3D/Skybox/miramar_dn.tga",
		"../External Resources/3D/Skybox/miramar_rt.tga",
		"../External Resources/3D/Skybox/miramar_lf.tga"
	};
	MainSkybox = new Skybox(SkyboxCubemapFaces, "./Shaders/SkyboxVertexShader.glsl", "./Shaders/SkyboxFragmentShader.glsl");
	DirLight = new Light(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
	PointLight = new Light(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
	SpotLight = new Light(MainCamera->Position, MainCamera->Front, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
}

void Renderer::Draw(Camera* _Camera, Entity* _Entity, Shader* _Shader)
{
	if (_Entity->m_Model) {
		_Shader->Activate();
		
		for (int i = 0; i < _Entity->m_Model->Meshes.size(); ++i) {

			_Entity->m_Model->ModelMatrix = glm::mat4(1.0f);
			_Entity->m_Model->ModelMatrix = glm::translate(_Entity->m_Model->ModelMatrix, _Entity->Position);
			/*_Entity->m_Model->ModelMatrix = glm::rotate(_Entity->m_Model->ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

			_Shader->SetMat4("ProjectionMatrix", MainCamera->ProjectionMatrix);
			_Shader->SetMat4("ViewMatrix", MainCamera->ViewMatrix);
			_Shader->SetMat4("ModelMatrix", _Entity->m_Model->ModelMatrix);

			_Shader->SetVec3("ViewPos", MainCamera->Position);

			int DiffuseCount = 1;
			int SpecularCount = 1;
			int NormalCount = 1;
			int HeightCount = 1;
			for (GLuint j = 0; j < _Entity->m_Model->Meshes[j].TextureCollection.size(); ++j) {
				glActiveTexture(GL_TEXTURE0 + j);
				std::string name;
				std::string number;
				TextureType type = _Entity->m_Model->Meshes[i].TextureCollection[j].type;

				switch (type) {
				case TextureType::DIFFUSE:
					name = "DiffuseMap";
					//number = std::to_string(DiffuseCount++);
					break;
				case TextureType::SPECULAR:
					name = "SpecularMap";
					//number = std::to_string(SpecularCount++);
					break;
				case TextureType::NORMAL:
					name = "NormalMap";
					//number = std::to_string(NormalCount++);
					break;
				case TextureType::HEIGHT:
					name = "HeightMap";
					//number = std::to_string(HeightCount++);
					break;
				}
				_Shader->SetInt("g_Material." + name + number, j);
				glBindTexture(GL_TEXTURE_2D, _Entity->m_Model->Meshes[i].TextureCollection[j].id);
			}
			_Shader->SetFloat("g_Material.Shininess", 64.0f);

			_Shader->SetVec3("g_Light.Position", glm::vec3(15.f, 15.f, -5.f));
			_Shader->SetVec3("g_Light.AmbientC", glm::vec3(0.5f, 0.5f, 0.5f));
			_Shader->SetVec3("g_Light.DiffuseC", glm::vec3(0.5f, 0.5f, 0.5f));
			_Shader->SetVec3("g_Light.SpecularC", glm::vec3(1.0f, 1.0f, 1.0f));

			glBindVertexArray(_Entity->m_Model->Meshes[i].VAO);
			glDrawElements(GL_TRIANGLES, _Entity->m_Model->Meshes[i].IndexCollection.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
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
	glDepthFunc(GL_LEQUAL);
	MainSkybox->Draw(MainCamera);
	glDepthFunc(GL_LESS);
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
	if (MainSkybox) {
		MainSkybox->Clear();
		delete MainSkybox;
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
	switch (_Type) {
	case ShaderType::BASIC:
		break;
	case ShaderType::TEXTURE:
		break;
	case ShaderType::SKYBOX:
		break;
	}
	return TempShader;
}