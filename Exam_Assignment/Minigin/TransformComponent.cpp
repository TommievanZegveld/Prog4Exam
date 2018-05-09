#include "MiniginPCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent() : mPosition(glm::vec3(0.0f, 0.0f, 0.0f))
{
}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::Render()
{
}

void TransformComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

void TransformComponent::Move(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}
