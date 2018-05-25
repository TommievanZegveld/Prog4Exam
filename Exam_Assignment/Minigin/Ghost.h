#pragma once
#include "Character.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>

class ColliderManager;
class Ghost final : public Character
{
public:
	Ghost();
	~Ghost();

	void Init() override;
	void Update(float deltaTime) override;
	std::vector<glm::vec2> GetSpawnPoints() const { return mSpawnPoints; }

	bool CheckCollisionInDirection(Direction dir, float deltaTime, float unitTest);
private:
	ColliderManager& mColliderManager;

	std::vector<glm::vec2> mSpawnPoints{
			glm::vec2(35,25),	// Top left
			glm::vec2(412,25),	// Top Right
			glm::vec2(35,446),	// Bottom left
			glm::vec2(412,446)	// Bottom right
	};
};

