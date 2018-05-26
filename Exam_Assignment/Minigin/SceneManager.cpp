#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void SceneManager::Update(float deltaTime)
{
	if(mNewActiveScene != nullptr)
	{
		// A new scene is to be showed; destroy current scene;
		if (mActiveScene)
		{
			mActiveScene->DestroyScene();
		}
		mActiveScene = mNewActiveScene;
		mNewActiveScene = nullptr;
		// Initialize scene;
		mActiveScene->Initialize();
	}

	if(mActiveScene != nullptr)
		mActiveScene->Update(deltaTime);
}

void SceneManager::Render()
{
	if (mActiveScene != nullptr)
		mActiveScene->Render();
}

void SceneManager::NextScene()
{
	for (size_t i = 0; i < mScenes.size(); i++)
	{
		if(mScenes[i] == mActiveScene)
		{
			auto nextScene = (++i) % mScenes.size();
			mNewActiveScene = mScenes[nextScene];
		}
	}
}

void SceneManager::PreviousScene()
{
	for (size_t i = 0; i < mScenes.size(); i++)
	{
		if (mScenes[i] = mActiveScene)
		{
			if (i == 0) i = mScenes.size();
			auto prevScene = (--i) % mScenes.size();
			mNewActiveScene = mScenes[prevScene];
		}
	}
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	if (mActiveScene == nullptr && mNewActiveScene == nullptr)
		mNewActiveScene = scene;

	mScenes.push_back(scene);
}
