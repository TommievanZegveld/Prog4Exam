#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"

dae::GameObject::GameObject()
{
	mTransform = new TransformComponent();
	AddComponent(mTransform);
}

dae::GameObject::~GameObject()
{
	for(auto com : mComponents)
	{
		delete com;
		com = nullptr;
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (int i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (int i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform->SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(BaseComponent* component)
{
	component->mGameObject = this;
	mComponents.push_back(component);
}

