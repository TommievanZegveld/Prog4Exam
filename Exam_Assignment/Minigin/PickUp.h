#pragma once
#include "GameObject.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>

class PickUp final : public GameObject
{
public:
	PickUp(glm::vec2 pos);
	~PickUp();

private:
	glm::vec2 mPosition;
};

