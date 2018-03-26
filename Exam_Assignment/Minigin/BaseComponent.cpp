#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <SDL.h>


dae::BaseComponent::BaseComponent() : mGameObject(nullptr)
{
}


dae::BaseComponent::~BaseComponent()
{
}

dae::TransformComponent* dae::BaseComponent::GetTransform() const
{
	if(mGameObject == nullptr)
	{
		std::stringstream ss; ss << "getTransform failed cuse gameObject is NULL" << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
	else return mGameObject->GetTransform();

}
