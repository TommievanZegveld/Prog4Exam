#pragma once
#include "SceneManager.h"

class GameObject;
class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(const std::shared_ptr<GameObject>& object);

	void Update(float deltaTime);
	void Render() const;

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private:
	explicit Scene(const std::string& name);

	std::string mName{};
	std::vector < std::shared_ptr<GameObject>> mObjects{};

	static unsigned int idCounter;
};