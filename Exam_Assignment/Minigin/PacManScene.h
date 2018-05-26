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

	const int mMaxGhosts = 4;
	const int mMaxPacman = 2;
	int mGhostCounter = 0;
	int mPacmanCounter = 0;

	const int mMaxKeyboard = 2;
	const int mMaxController = 4;
	int mKeyBoardCounter = 0;
	int mControllerCounter = 0;

	int mPlayerCounter = 0;
};

