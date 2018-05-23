#pragma once
#include "GameObject.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>

class Wall final : public GameObject
{
public:
	Wall(glm::vec2 pos,int width,int height);
	~Wall();

private:
	int mWidth, mHeight;
	glm::vec2 mPosition;
};

