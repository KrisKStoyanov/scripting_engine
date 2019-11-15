#include "Renderer.h"

namespace Cyberspace {
	Renderer* Renderer::Create(EngineWindow*& _window, const GraphicsProps& _props)
	{
		return new Renderer(_window, _props);
	}

	Renderer::Renderer(EngineWindow*& _window, const GraphicsProps& _props)
	{
		Init(_window, _props);
	}

	Renderer::~Renderer()
	{
		Terminate();
	}

	void Renderer::Init(EngineWindow*& _window, const GraphicsProps& _props)
	{
		glewExperimental = GL_TRUE;
		GLenum initState = glewInit();
		if (initState != GLEW_OK) {
			fprintf(stderr, "Error: %s\n", glewGetErrorString(initState));
		}

		glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		
		_window->SetVSync(_props.windowProps.VSync);
		m_GUI = std::unique_ptr<GUIToolkit>(GUIToolkit::Create(_window, _props.guiProps));
		MainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), _props.FOV, _props.windowProps.Width, _props.windowProps.Height);
		
		Setup(_props);
	}

	void Renderer::Setup(const GraphicsProps& _props)
	{
		MainSkybox = new Skybox(_props.SkyboxFaceTexturePaths);
		DirLight = new Light(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f));
		
		//PointLight = new Light(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
		//SpotLight = new Light(MainCamera->Position, MainCamera->Front, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
	}

	void Renderer::Draw(Camera* _Camera, Model* _Model, Transform* _Transform, Shader* _Shader)
	{
		_Shader->Activate();

		for (int i = 0; i < _Model->Meshes.size(); ++i) {
			_Transform->Translate(_Transform->GetPosition());
			_Shader->SetMat4("ProjectionMatrix", MainCamera->ProjectionMatrix);
			_Shader->SetMat4("ViewMatrix", MainCamera->ViewMatrix);
			_Shader->SetMat4("ModelMatrix", _Transform->GetModelMatrix());

			_Shader->SetVec3("ViewPos", MainCamera->GetTransform()->GetPosition());

			for (GLuint j = 0; j < _Model->Meshes[i].TextureCollection.size(); ++j) {
				glActiveTexture(GL_TEXTURE0 + j);
				_Shader->SetInt("g_Material.TextureMap", j);
				glBindTexture(GL_TEXTURE_2D, _Model->Meshes[i].TextureCollection[j].ID);
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

			glBindVertexArray(_Model->Meshes[i].VAO);
			glDrawElements(GL_TRIANGLES, _Model->Meshes[i].IndexCollection.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	void Renderer::OnUpdate(std::queue<CyberEvent*>& _BlockingEventQueue, std::queue<CyberEvent*>& _EventQueue, std::unordered_map<std::string, Shader*> _ShaderMap, std::unordered_map<std::string, Entity*> _EntityMap, double _CursorPosX, double _CursorPosY, float _DeltaTime)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (!_BlockingEventQueue.empty()) {
			std::vector<EventTag>::iterator Tag = std::find(_BlockingEventQueue.front()->Tags.begin(), _BlockingEventQueue.front()->Tags.end(), EventTag::GRAPHICS);
			if (Tag != _BlockingEventQueue.front()->Tags.end()) {
				_BlockingEventQueue.front()->Tags.erase(Tag);
				switch (_BlockingEventQueue.front()->Type) {
				case EventType::TOGGLE_CAMERA_MOVEMENT:
					m_EnableCameraMovement = !m_EnableCameraMovement;
					if (_BlockingEventQueue.front()->Tags.empty()) {
						_BlockingEventQueue.pop();
					}
					break;
				case EventType::TOGGLE_GUI:
					m_ToggleGUI = !m_ToggleGUI;
					if (_BlockingEventQueue.front()->Tags.empty()) {
						_BlockingEventQueue.pop();
					}
					break;
				}
			}
		}
		if (!_EventQueue.empty()) {
			std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::GRAPHICS);
			if (Tag != _EventQueue.front()->Tags.end()) {
				_EventQueue.front()->Tags.erase(Tag);
				switch (_EventQueue.front()->Type) {

				case EventType::CAMERA_MOVE_FORWARD:
					if (m_EnableCameraMovement)
						MainCamera->UpdateTransformKeyboard(MovementType::FORWARD, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::CAMERA_MOVE_BACKWARD:
					if (m_EnableCameraMovement)
						MainCamera->UpdateTransformKeyboard(MovementType::BACKWARD, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::CAMERA_MOVE_LEFT:
					if (m_EnableCameraMovement)
						MainCamera->UpdateTransformKeyboard(MovementType::LEFT, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;

				case EventType::CAMERA_MOVE_RIGHT:
					if (m_EnableCameraMovement)
						MainCamera->UpdateTransformKeyboard(MovementType::RIGHT, _DeltaTime);
					if (_EventQueue.front()->Tags.empty()) {
						_EventQueue.pop();
					}
					break;
				default:
					break;
				}
			}
		}
		for (std::pair<std::string, Entity*> iter : _EntityMap) {
			Draw(MainCamera, iter.second->GetModel(), iter.second->GetTransform(), _ShaderMap["Model"]);
		}
		if (m_EnableCameraMovement) {
			MainCamera->UpdateTransformMouse(_CursorPosX, -_CursorPosY);
		}
		glDepthFunc(GL_LEQUAL);
		MainSkybox->Draw(MainCamera, _ShaderMap["Skybox"]);
		glDepthFunc(GL_LESS);
		if (m_ToggleGUI) {
			m_GUI->OnUpdate(_BlockingEventQueue, _EventQueue);
		}	
	}

	void Renderer::Terminate()
	{
		if (MainSkybox) {
			delete MainSkybox;
		}
		if (MainCamera) {
			delete MainCamera;
		}
		m_GUI.reset();
	}
}
