#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "Components.h"

GameObject::GameObject()
{
	mTransform = std::make_shared<TransformComponent>();
	AddComponent(mTransform);
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < mComponents.size(); ++i)
	{
		mComponents[i]->Update(deltaTime);
	}
}

void GameObject::SetPosition(float x, float y)
{
	mTransform->SetPosition(x, y, 0.0f);
}

void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	component->mGameObject = this;

	for (auto comp : mComponents)
	{
		if(typeid(*comp) == typeid(*component))
		{

			std::cout << "ERROR: You're trying to add a component of which there is already one attached to the GameObject\nComponent not added" << std::endl;
			throw std::runtime_error("Cannot add a 2nd component to a GameObject that already has one");
			return;			
		}
	}
	const type_info& ti = typeid(RenderComponent);
	if (component && typeid(*component) == ti)
	{
		Renderer::GetInstance().AddRenderComponent(std::static_pointer_cast<RenderComponent>(component));
	}

	mComponents.push_back(component);
}

