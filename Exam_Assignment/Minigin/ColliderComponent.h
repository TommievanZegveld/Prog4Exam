#pragma once
#include "BaseComponent.h"

enum class ColliderType
{
	STATIC,
	DYNAMIC,
	TRIGGER
};
class ColliderComponent final : public BaseComponent
{
public:

	ColliderComponent(ColliderType t, int width, int height);
	~ColliderComponent();

	void Update(float dT);

private:
	ColliderType mType;
	int mWidth, mHeight;
};

