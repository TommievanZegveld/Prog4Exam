#pragma once
#include "BaseComponent.h"
#include "Types.h"

class RectangleComponent final : public BaseComponent
{
public:
	RectangleComponent(float width,float height,Color col);
	~RectangleComponent();

	void Update(float deltaTime) override;

private:
	float mWidth, mHeight;
	Color mCol;

};

