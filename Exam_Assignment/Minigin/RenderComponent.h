#pragma once
#include "BaseComponent.h"

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	void Render();
};