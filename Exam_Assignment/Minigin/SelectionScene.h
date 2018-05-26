#pragma once
#include "Scene.h"

class SelectionScene final : public Scene
{
public:
	SelectionScene();
	~SelectionScene();

	void Update(float deltaTime) override;

	void Initialize() override;


};

