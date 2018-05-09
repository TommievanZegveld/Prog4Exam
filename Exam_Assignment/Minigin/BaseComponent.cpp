#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <SDL.h>


BaseComponent::BaseComponent() : mGameObject(nullptr)
{
}


BaseComponent::~BaseComponent()
{
}

GameObject * BaseComponent::GetGameObject() const
{
	return mGameObject;
}
