#include "MiniginPCH.h"
#include "ColliderComponent.h"



ColliderComponent::ColliderComponent(ColliderType t,int width,int height) : mWidth(width),mHeight(height),mType(t)
{
}


ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Update(float dT)
{
	UNREFERENCED_PARAMETER(dT);
}
