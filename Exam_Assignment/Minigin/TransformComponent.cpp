#include "MiniginPCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent() : mPosition(glm::vec2(0.0f, 0.0f))
{
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TransformComponent::SetPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void TransformComponent::Move(float x, float y)
{
	mPosition.x += x;
	mPosition.y += y;
}
