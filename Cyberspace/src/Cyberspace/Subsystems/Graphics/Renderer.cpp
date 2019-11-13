#include "Renderer.h"

namespace Cyberspace {
	Renderer* Renderer::Create(const GraphicsProps& _props)
	{
		return new Renderer(_props);
	}
	Renderer::Renderer(const GraphicsProps& _props)
	{
		Init(_props);
	}

	Renderer::~Renderer()
	{
		Terminate();
	}

	void Renderer::Init(const GraphicsProps& _props)
	{
		glewExperimental = GL_TRUE;
		GLenum initState = glewInit();
		if (initState != GLEW_OK) {
			fprintf(stderr, "Error: %s\n", glewGetErrorString(initState));
		}

		glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		Setup(_props);
	}

	void Renderer::Setup(const GraphicsProps& _props)
	{
		MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), _props.FOV, _props.Width, _props.Height);
		MainSkybox = new Skybox(_props.SkyboxFaceTexturePaths);
		DirLight = new Light(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
		//PointLight = new Light(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
		//SpotLight = new Light(MainCamera->Position, MainCamera->Front, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
	}

	void Renderer::Draw(Camera* _Camera, Entity* _Entity, Shader* _Shader)
	{
		if (_Entity->m_Model) {
			_Shader->Activate();

			for (int i = 0; i < _Entity->m_Model->Meshes.size(); ++i) {

				_Entity->GetTransform()->Translate();
				/*_Entity->m_Model->ModelMatrix = glm::rotate(_Entity->m_Model->ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

				_Shader->SetMat4("ProjectionMatrix", MainCamera->ProjectionMatrix);
				_Shader->SetMat4("ViewMatrix", MainCamera->ViewMatrix);
				_Shader->SetMat4("ModelMatrix", _Entity->GetTransform()->GetModelMatrix());

				_Shader->SetVec3("ViewPos", MainCamera->GetTransform()->GetPosition());

				for (GLuint j = 0; j < _Entity->m_Model->Meshes[i].TextureCollection.size(); ++j) {
					glActiveTexture(GL_TEXTURE0 + j);
					_Shader->SetInt("g_Material.TextureMap", j);
					glBindTexture(GL_TEXTURE_2D, _Entity->m_Model->Meshes[i].TextureCollection[j].ID);
				}
				_Shader->SetFloat("g_Material.Shininess", 64.0f);

				if (DirLight) {
					_Shader->SetVec3("g_DirLight.Direction", DirLight->Direction);
					_Shader->SetVec3("g_DirLight.AmbientC", DirLight->AmbientC);
					_Shader->SetVec3("g_DirLight.DiffuseC", DirLight->DiffuseC);
					_Shader->SetVec3("g_DirLight.SpecularC", DirLight->SpecularC);
				}

				if (PointLight) {
					_Shader->SetVec3("g_PointLight.Position", PointLight->Position);
					_Shader->SetVec3("g_PointLight.AmbientC", PointLight->AmbientC);
					_Shader->SetVec3("g_PointLight.DiffuseC", PointLight->DiffuseC);
					_Shader->SetVec3("g_PointLight.SpecularC", PointLight->SpecularC);
					_Shader->SetFloat("g_PointLight.ConstantA", PointLight->ConstantA);
					_Shader->SetFloat("g_PointLight.LinearA", PointLight->LinearA);
					_Shader->SetFloat("g_PointLight.QuadraticA", PointLight->QuadraticA);
				}

				if (SpotLight) {
					_Shader->SetVec3("g_SpotLight.Position", SpotLight->Position);
					_Shader->SetVec3("g_SpotLight.Direction", SpotLight->Direction);
					_Shader->SetVec3("g_SpotLight.AmbientC", SpotLight->AmbientC);
					_Shader->SetVec3("g_SpotLight.DiffuseC", SpotLight->DiffuseC);
					_Shader->SetVec3("g_SpotLight.SpecularC", SpotLight->SpecularC);
					_Shader->SetFloat("g_SpotLight.ConstantA", SpotLight->ConstantA);
					_Shader->SetFloat("g_SpotLight.LinearA", SpotLight->LinearA);
					_Shader->SetFloat("g_SpotLight.QuadraticA", SpotLight->QuadraticA);
					_Shader->SetFloat("g_SpotLight.CutOff", SpotLight->CutOff);
					_Shader->SetFloat("g_SpotLight.OuterCutOff", SpotLight->OuterCutOff);
				}

				glBindVertexArray(_Entity->m_Model->Meshes[i].VAO);
				glDrawElements(GL_TRIANGLES, _Entity->m_Model->Meshes[i].IndexCollection.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
		}
	}

	void Renderer::OnUpdate(std::queue<CyberEvent*>& _EventQueue, std::unordered_map<std::string, Shader*> _ShaderMap, std::map<EntityTag, Entity*> _EntityCollection, double _CursorPosX, double _CursorPosY, std::vector<glm::vec3>& _updatedPositions, float _DeltaTime)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (!_EventQueue.empty()) {
			std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::GRAPHICS);
			if (Tag != _EventQueue.front()->Tags.end()) {
				_EventQueue.front()->Tags.erase(Tag);
				switch (_EventQueue.front()->Type) {

				case EventType::CAMERA_MOVE_FORWARD:
					MainCamera->UpdateTransformKeyboard(MovementType::FORWARD, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::CAMERA_MOVE_BACKWARD:
					MainCamera->UpdateTransformKeyboard(MovementType::BACKWARD, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::CAMERA_MOVE_LEFT:
					MainCamera->UpdateTransformKeyboard(MovementType::LEFT, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::CAMERA_MOVE_RIGHT:
					MainCamera->UpdateTransformKeyboard(MovementType::RIGHT, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::VEHICLE_MOVE_FORWARD:

					_EntityCollection[EntityTag::MainCharacter]->GetTransform()->Translate(
						_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition() +
						_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetOrientation()
						* 50.0f * _DeltaTime);

					_EventQueue.push(new CyberEvent(EventType::UPDATE_POSITIONS, EventTag::NETWORK));
					_updatedPositions.push_back(_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition());
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::VEHICLE_MOVE_BACKWARD:

					_EntityCollection[EntityTag::MainCharacter]->GetTransform()->Translate(
						_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition() +
						-_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetOrientation()
						* 50.0f * _DeltaTime);

					_EventQueue.push(new CyberEvent(EventType::UPDATE_POSITIONS, EventTag::NETWORK));
					_updatedPositions.push_back(_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition());
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::VEHICLE_MOVE_LEFT:
					_EntityCollection[EntityTag::MainCharacter]->GetTransform()->Translate(
						_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition() +
						-_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetRightDir()
						* 50.0f * _DeltaTime);

					_EventQueue.push(new CyberEvent(EventType::UPDATE_POSITIONS, EventTag::NETWORK));
					_updatedPositions.push_back(_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition());
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::VEHICLE_MOVE_RIGHT:
					_EntityCollection[EntityTag::MainCharacter]->GetTransform()->Translate(
						_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition() +
						_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetRightDir()
						* 50.0f * _DeltaTime);
					_EventQueue.push(new CyberEvent(EventType::UPDATE_POSITIONS, EventTag::NETWORK));
					_updatedPositions.push_back(_EntityCollection[EntityTag::MainCharacter]->GetTransform()->GetPosition());
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				default:
					break;
				}
			}
		}
		for (std::pair<EntityTag, Entity*> iter : _EntityCollection) {
			Draw(MainCamera, iter.second, _ShaderMap["Model"]);
		}
		MainCamera->UpdateTransformMouse(_CursorPosX, -_CursorPosY);
		glDepthFunc(GL_LEQUAL);
		MainSkybox->Draw(MainCamera, _ShaderMap["Skybox"]);
		glDepthFunc(GL_LESS);
	}

	void Renderer::Terminate()
	{
		if (MainSkybox) {
			delete MainSkybox;
		}
		if (MainCamera) {
			delete MainCamera;
		}
	}
}
