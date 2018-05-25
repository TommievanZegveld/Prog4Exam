#pragma once
#include "PickUp.h"

class SpecialPickUp final : public PickUp
{
public:
	SpecialPickUp(glm::vec2 pos);
	~SpecialPickUp();

	void Init() override;
};

