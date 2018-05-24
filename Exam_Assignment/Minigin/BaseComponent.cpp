#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <SDL.h>


BaseComponent::BaseComponent()
{
}


BaseComponent::~BaseComponent()
{
}

std::weak_ptr<GameObject> BaseComponent::GetGameObject() const
{
	return mGameObject;
}
