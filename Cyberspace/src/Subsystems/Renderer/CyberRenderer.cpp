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

	MainCamera = new Camera(glm::vec3(0.0f,0.0f,3.0f), 60, _WindowWidth, _WindowHeight);
	MainCamera->SetupShader("./Shaders/vert.glsl", "./Shaders/frag.glsl");

	return true;
}

void CyberRenderer::Draw(GLuint _VAO, GLuint _ElementCount)
{
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _ElementCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
	
void CyberRenderer::Update(std::queue<CyberEvent*>& _EventQueue, std::vector<Entity*> _EntityCollection)
{
	if (!_EventQueue.empty()) {
		std::vector<EventTag>::iterator Tag = std::find(_EventQueue.front()->Tags.begin(), _EventQueue.front()->Tags.end(), EventTag::GRAPHICS);
		if (Tag != _EventQueue.front()->Tags.end()) {
			_EventQueue.front()->Tags.erase(Tag);
			//switch (_EventQueue.front()->Type) {
			//case EventType::MOVE_FORWARD:
			//	TestEntity->Position += glm::vec3(0, 0.001f, 0);
			//	printf("MOVE_FORWARD EVENT\n");
			//	break;
			//case EventType::MOVE_BACKWARD:
			//	TestEntity->Position += glm::vec3(0, -0.001f, 0);
			//	printf("MOVE_BACKWARD EVENT\n");
			//	break;
			//case EventType::MOVE_LEFT:
			//	TestEntity->Position += glm::vec3(-0.001f, 0, 0);
			//	printf("MOVE_LEFT EVENT\n");
			//	break;
			//case EventType::MOVE_RIGHT:
			//	TestEntity->Position += glm::vec3(0.001f, 0, 0);
			//	printf("MOVE_RIGHT EVENT\n");
			//	break;
			//default:
			//	break;
			//}
			if (_EventQueue.front()->Tags.empty()) {
				_EventQueue.pop();
			}
		}
	}
	for (Entity* E : _EntityCollection) {
		if (E->GFX_Comp != NULL) {
			E->GFX_Comp->ModelMatrix = glm::mat4(1.0f);
			E->GFX_Comp->ModelMatrix = glm::translate(E->GFX_Comp->ModelMatrix, E->Position);
			E->GFX_Comp->ModelMatrix = glm::rotate(E->GFX_Comp->ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			MainCamera->Update(E->GFX_Comp->ModelMatrix);
			Draw(E->GFX_Comp->VAO, E->GFX_Comp->IndexCollection.size());
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

}

