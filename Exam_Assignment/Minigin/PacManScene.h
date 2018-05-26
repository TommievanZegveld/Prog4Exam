#pragma once
#include "Scene.h"

class Character;

class PacManScene final : public Scene
{
public:
	PacManScene();
	~PacManScene();

	void Update(float deltaTime) override;

	void Initialize() override;
	void DestroyLocals() override;

private:
	std::vector<std::shared_ptr<Character>> mActivePlayers;
	std::vector<std::shared_ptr<GameObject>> mScoreObjects;
};

