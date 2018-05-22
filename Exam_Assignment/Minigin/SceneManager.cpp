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

//Scene& SceneManager::CreateScene(const std::string& name)
//{
//	const auto scene = std::shared_ptr<Scene>(new Scene(name));
//	mScenes.push_back(scene);
//	return *scene;
//}

void SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	mScenes.push_back(scene);
	scene->Initialize();
}
