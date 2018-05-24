#include "MiniginPCH.h"
#include "PickUp.h"
#include "Components.h"


PickUp::PickUp(glm::vec2 pos) : mPosition(pos)
{

}


PickUp::~PickUp()
{
}

void PickUp::Init()
{
	GameObject::Init();

	auto collider = std::make_shared<ColliderComponent>(mPosition, 5.f, 5.f, ColliderType::STATIC);
	AddComponent(collider);
	auto rect = std::make_shared<RectangleComponent>(5.f, 5.f,Color{255,255,0});
	AddComponent(rect);
	SetPosition(mPosition.x, mPosition.y);
}
