#pragma once
#include "GameObject.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>

enum class Direction;
class ColliderManager;

class Teleporter final : public GameObject
{
public:
	Teleporter(glm::vec2 pos1, Direction dir,glm::vec2 pos2);
	~Teleporter();

	void Init() override;
	void Update(float deltaTime) override;
private:
	glm::vec2 mPosition, mToPosition;
	Direction mAllowDirection;

	ColliderManager& mColliderManager;
};

