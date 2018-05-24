#include "MiniginPCH.h"
#include "Wall.h"
#include "Components.h"

Wall::Wall(glm::vec2 pos, int width, int height) : mPosition(pos), mWidth(width), mHeight(height)
{

}


Wall::~Wall()
{
}

void Wall::Init()
{
	//	Attaching Transform from original GameObject
	GameObject::Init();

	auto collider = std::make_shared<ColliderComponent>(mPosition, (float)mWidth, (float)mHeight, ColliderType::STATIC);
	AddComponent(collider);
	auto rect = std::make_shared<RectangleComponent>((float)mWidth, (float)mHeight, Color{ 0,0,255 });
	AddComponent(rect);
	SetPosition(mPosition.x, mPosition.y);
}
