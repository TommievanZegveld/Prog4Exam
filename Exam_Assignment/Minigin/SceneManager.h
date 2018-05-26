#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	//Scene & CreateScene(const std::string& name);
	void AddScene(std::shared_ptr<Scene> scene);

	void Update(float deltaTime);
	void Render();

	void NextScene();
	void PreviousScene();

private:
	std::vector<std::shared_ptr<Scene>> mScenes;

	std::shared_ptr<Scene> mActiveScene;
	std::shared_ptr<Scene> mNewActiveScene;
};
