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
	Direction GetDirection() const { return mCurrentDir; }
private:
	Direction mCurrentDir;
};

