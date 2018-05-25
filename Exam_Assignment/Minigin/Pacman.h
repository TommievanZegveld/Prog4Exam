#pragma once
#include "Character.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>

class ColliderManager;

class Pacman final : public Character
{
public:
	Pacman();
	~Pacman();

	void Init() override;
	void Update(float deltaTime) override;
	std::vector<std::shared_ptr<GameObject>> GetDestroyFlaggedActor() { return mToDestroy; }

	int GetScore() { return mScore; }
	int GetLives() { return mLives; }
	glm::vec2 GetSpawnPoint() { return mSpawnPoint; }

	bool CheckCollisionInDirection(Direction dir,float deltaTime,float unitTest);

private:
	ColliderManager& mColliderManager;

	int mScore = 0;
	int mLives = 3;
	bool mSuperState = false;
	float mSuperTime = 5.f;
	float mSuperTimer = 0;
	glm::vec2 mSpawnPoint = glm::vec2(224, 266);
	std::vector<std::shared_ptr<GameObject>> mToDestroy;
};

