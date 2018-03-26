#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent() : mPosition(glm::vec3(0.0f, 0.0f, 0.0f))
{
}


dae::TransformComponent::~TransformComponent()
{
}

void dae::TransformComponent::Render()
{
}

void dae::TransformComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

void dae::TransformComponent::Move(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}
