#pragma once
#include "PickUp.h"

class Fruit final : public PickUp
{
public:
	Fruit(glm::vec2 pos);
	~Fruit();

	void Init() override;
private:
	std::vector<std::string> mFruits = { "apple.png","cherry.png","orange.png","strawberry.png","grape.png" };
};

