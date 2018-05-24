#pragma once
#include "Character.h"

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

	bool CheckCollisionInDirection(Direction dir,float deltaTime,float unitTest);

private:
	ColliderManager& mColliderManager;

	int mScore = 0;

	std::vector<std::shared_ptr<GameObject>> mToDestroy;
};

