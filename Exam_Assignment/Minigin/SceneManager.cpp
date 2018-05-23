#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void SceneManager::Update(float deltaTime)
{
	for(auto scene : mScenes)
	{
		scene->Update(deltaTime);
	}
}

void SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	mScenes.push_back(scene);
	scene->Initialize();
}
