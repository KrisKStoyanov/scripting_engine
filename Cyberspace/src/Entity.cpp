#include "Entity.h"

Entity::Entity(glm::vec3 _Position, glm::vec3 _Direction)
{
	Position = _Position;
	Direction = _Direction;
}

Entity::~Entity()
{
}

void Entity::Setup(GraphicsComponent* _GFX, PhysicsComponent* _PSX , AudioComponent* _Audio)
{
	if (_GFX->Setup()) {
		GFX_Comp = _GFX;
	}
	if (_PSX->Setup()) {
		PSX_Comp = _PSX;
	}
	if (_Audio->Setup()) {
		Audio_Comp = _Audio;
	}
}

void Entity::Clear()
{
	if (GFX_Comp != NULL) {
		GFX_Comp->Clear();
		GFX_Comp = nullptr;
	}

	if (PSX_Comp != NULL) {
		PSX_Comp->Clear();
		PSX_Comp = nullptr;
	}

	if (Audio_Comp != NULL) {
		Audio_Comp->Clear();
		Audio_Comp = nullptr;
	}
}

