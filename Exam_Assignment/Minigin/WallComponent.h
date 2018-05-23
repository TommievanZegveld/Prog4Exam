#pragma once
#include "BaseComponent.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec3.hpp>
#include <SDL.h>

struct WallSize
{
	float width, height;
};

class WallComponent final : public BaseComponent
{
public:
	WallComponent();
	~WallComponent();

	WallSize GetWallSize();

private:
	WallSize mWallSize;
	glm::vec3 mPosition;


};

