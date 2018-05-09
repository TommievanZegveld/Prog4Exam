#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"

GameObject::GameObject()
{
	mTransform = new TransformComponent();
	AddComponent(mTransform);
}

GameObject::~GameObject()
{
	for(auto com : mComponents)
	{
		delete com;
		com = nullptr;
	}
}

void GameObject::Update(float deltaTime)
{
	for (int i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->Update(deltaTime);
	}
}

void GameObject::Render() const
{
	for (int i = 0; i < mComponents.size(); i++)
	{
		mComponents[i]->Render();
	}
}

void GameObject::SetPosition(float x, float y)
{
	mTransform->SetPosition(x, y, 0.0f);
}

void GameObject::AddComponent(BaseComponent* component)
{
	//component->mGameObject = this;
	mComponents.push_back(component);
}

