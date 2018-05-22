#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "Renderer.h"

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

//void Scene::Update(const float deltaTime)
//{
//	for(auto gameObject : mObjects)
//	{
//		gameObject->Update(deltaTime);
//	}
//}

void Scene::Render() const
{
	auto& renderer = Renderer::GetInstance();
	renderer.Render();
}

