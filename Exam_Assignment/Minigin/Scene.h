#pragma once
#include "SceneManager.h"

class GameObject;
class Scene
{
//	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(const std::shared_ptr<GameObject>& object);
	virtual void Initialize();

	Scene(const std::string& name);
	virtual void Update(float deltaTime) = 0;
	void Render() const;

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

protected:
	std::vector < std::shared_ptr<GameObject>> mObjects{};
private:

	std::string mName{};

	static unsigned int idCounter;
};