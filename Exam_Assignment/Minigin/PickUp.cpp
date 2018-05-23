#include "MiniginPCH.h"
#include "PickUp.h"
#include "Components.h"


PickUp::PickUp(glm::vec2 pos) : mPosition(pos)
{
	auto collider = std::make_shared<ColliderComponent>(mPosition, 5.f, 5.f, ColliderType::STATIC);
	AddComponent(collider);
	auto rect = std::make_shared<RectangleComponent>(5.f, 5.f);
	AddComponent(rect);
	SetPosition(mPosition.x, mPosition.y);
}


PickUp::~PickUp()
{
}