#pragma once
#include "BaseComponent.h"

class RectangleComponent final : public BaseComponent
{
public:
	RectangleComponent(float width,float height);
	~RectangleComponent();

	void Update(float deltaTime) override;

private:
	float mWidth, mHeight;

};

