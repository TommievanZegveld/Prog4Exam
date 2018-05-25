#include "MiniginPCH.h"
#include "SpecialPickUp.h"
#include "Components.h"


SpecialPickUp::SpecialPickUp(glm::vec2 pos) : PickUp(pos)
{
}


SpecialPickUp::~SpecialPickUp()
{
}

void SpecialPickUp::Init()
{
	GameObject::Init();

	auto collider = std::make_shared<ColliderComponent>(mPosition, 10.f, 10.f, ColliderType::STATIC);
	AddComponent(collider);
	auto rect = std::make_shared<RectangleComponent>(10.f, 10.f, Color{ 255,255,0 });
	AddComponent(rect);
	SetPosition(mPosition.x, mPosition.y);
	mScoreValue = 5;
}

