#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "Components.h"
#include "ColliderManager.h"

GameObject::GameObject()
{
	
}

GameObject::~GameObject()
{
	auto test = 0;
	std::cout << test << std::endl;
	
}

void GameObject::Init()
{
	mTransform = std::make_shared<TransformComponent>();
	AddComponent(mTransform);
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
	mTransform->SetPosition(x, y);
}

void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	component->mGameObject = shared_from_this();

	for (auto comp : mComponents)
	{
		if(typeid(*comp) == typeid(*component))
		{
			std::cout << "ERROR: You're trying to add a component of which there is already one attached to the GameObject\nComponent not added" << std::endl;
			throw std::runtime_error("Cannot add a 2nd component to a GameObject that already has one");		
		}
	}

	// Add renderComponent to renderer for rendering
	const type_info& ti = typeid(RenderComponent);
	if (component && typeid(*component) == ti)
	{
		Renderer::GetInstance().AddRenderComponent(std::static_pointer_cast<RenderComponent>(component));
	}

	//	Add Colliders to ColliderManager
	const type_info& ti2 = typeid(ColliderComponent);
	if (component && typeid(*component) == ti2)
	{
		auto test = std::static_pointer_cast<ColliderComponent>(component);
		auto type = test->mType;
		auto& colliderManager = ColliderManager::GetInstance();

		if (type == ColliderType::DYNAMIC)
			colliderManager.AddDynamic(std::static_pointer_cast<ColliderComponent>(component));
		if (type == ColliderType::STATIC)
			colliderManager.AddStatic(std::static_pointer_cast<ColliderComponent>(component));
		if (type == ColliderType::TRIGGER)
			colliderManager.AddTrigger(std::static_pointer_cast<ColliderComponent>(component));
	}

	mComponents.push_back(component);
}

