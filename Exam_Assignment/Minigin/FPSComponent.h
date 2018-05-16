#pragma once
#include "TextComponent.h"	

class FPSComponent final : public TextComponent
{
public:
	FPSComponent();
	~FPSComponent();

	void Update(float dt);
	void Render();

};
