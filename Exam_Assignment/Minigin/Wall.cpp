#include "MiniginPCH.h"
#include "Wall.h"
#include "Components.h"

Wall::Wall(glm::vec2 pos, int width, int height) : mPosition(pos), mWidth(width), mHeight(height)
{
	auto collider = std::make_shared<ColliderComponent>(mPosition, (float)mWidth, (float)mHeight, ColliderType::STATIC);
	AddComponent(collider);
	auto rect = std::make_shared<RectangleComponent>((float)mWidth, (float)mHeight);
	AddComponent(rect);
	SetPosition(mPosition.x, mPosition.y);
}


Wall::~Wall()
{
}
