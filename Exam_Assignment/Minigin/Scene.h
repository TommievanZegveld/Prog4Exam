#pragma once
#include "SceneManager.h"

class GameObject;

class Scene
{
//	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(const std::shared_ptr<GameObject>& object);
	virtual void Initialize() = 0;

	Scene(const std::string& name);
	virtual void Update(float deltaTime);
	void Render() const;
	void FlagForDestruction(std::shared_ptr<GameObject> obj);
	void DestroyObjects();

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

protected:
	friend class GameObject;
	std::vector < std::shared_ptr<GameObject>> mObjects{};
	std::vector < std::shared_ptr<GameObject>> mToDelete{};

private:

	std::string mName{};

	static unsigned int idCounter;
};