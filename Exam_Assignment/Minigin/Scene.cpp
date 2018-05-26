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
	object->Init();
	mObjects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for (auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void Scene::Render() const
{
	auto& renderer = Renderer::GetInstance();
	renderer.Render();
}

void Scene::FlagForDestruction(std::shared_ptr<GameObject> obj)
{
	for (size_t i = 0; i < mObjects.size(); i++)
	{
		if (obj == mObjects[i])
			mToDelete.push_back(mObjects[i]);
	}
}

void Scene::DestroyObjects()
{
	for (size_t i = 0; i < mToDelete.size(); i++)
	{
		if (std::find(mObjects.begin(), mObjects.end(), mToDelete.at(i)) != mObjects.end())
		{
			// Remove Render Component if available from Renderer
			Renderer::GetInstance().RemoveRenderComponent(mToDelete.at(i));
			//	Remove the collider component from the collidermanager 
			ColliderManager::GetInstance().RemoveCollider(mToDelete.at(i));
			mObjects.erase(std::remove(mObjects.begin(), mObjects.end(), mToDelete.at(i)));
		}
	}
}

void Scene::DestroyScene()
{
	// Objects already flagged for destruction should be destroyed first
	DestroyObjects();
	//	Local vectors should be cleared aswell; in case there is only 1 scene the shared pointer
	//	Never goes out of scope so if within the intialize we add to these local vectors
	//	the vector continues growing; which is undesirable;
	DestroyLocals();

	for (size_t i = 0; i < mObjects.size(); i++)
	{
		// Remove Render Component if available from Renderer
		Renderer::GetInstance().RemoveRenderComponent(mObjects.at(i));
		//	Remove the collider component from the collidermanager 
		ColliderManager::GetInstance().RemoveCollider(mObjects.at(i));
	}
	mObjects.clear();
}

void Scene::DestroyLocals()
{
}

