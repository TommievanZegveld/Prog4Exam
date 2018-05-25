#pragma once
#include "GameObject.h"

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class Character : public GameObject
{
public:
	Character();
	~Character();

	void SetDirection(Direction dir);
	void SetNextDirection(Direction dir);
	Direction GetDirection() const { return mCurrentDir; }

	void SetSpeed(float speed) {mSpeed = speed; }
	float GetSpeed() { return mSpeed; }

	bool CheckCollisionInDirection(Direction dir, float deltaTime, float unitTest);

protected:
	Direction mCurrentDir;
	Direction mNextDir;
	float mSpeed = 100.f;
};

