#pragma once
#include "Character.h"
class Pacman final : public Character
{
public:
	Pacman();
	~Pacman();

	void Init() override;
	void Update(float deltaTime) override;
};

