#pragma once
#include "Entity.h"

class GameObject : public Entity
{
public:
	GameObject(glm::vec3 _Position);
	~GameObject();

	virtual Entity* Clone (glm::vec3 _Position){
		return new GameObject(_Position);
	}
};

