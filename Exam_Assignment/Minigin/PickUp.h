#pragma once
#include "GameObject.h"
#pragma warning (disable:4201)
#include <glm/detail/type_vec2.hpp>

class PickUp : public GameObject
{
public:
	PickUp(glm::vec2 pos);
	~PickUp();
	int GetScore() { return mScoreValue; }
	void Init() override;
protected:
	glm::vec2 mPosition;
	int mScoreValue = 0;
};

