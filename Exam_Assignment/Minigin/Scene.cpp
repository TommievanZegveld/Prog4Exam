#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ColliderManager.h"
#include <algorithm>

unsigned int Scene::idCounter = 0;

Scene::Scene(const std::string& name) : mName(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	mObjects.push_back(object);
}

void Scene::Initialize()
{
}

void Scene::Render() const
{
	auto& renderer = Renderer::GetInstance();
	renderer.Render();
}

void Scene::DestroyObjects()
{
	for (size_t i = 0; i < mToDelete.size(); i++)
	{
		if (std::find(mObjects.begin(), mObjects.end(), mToDelete.at(i)) != mObjects.end())
		{
			// Remove Render Component if available from Renderer
			Renderer::GetInstance().RemoveRenderComponent(mToDelete.at(i));
			ColliderManager::GetInstance().RemoveCollider(mToDelete.at(i));
			//	Remove the collider component from the collidermanager 
			mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), mToDelete.at(i)));
		}
	}
}

