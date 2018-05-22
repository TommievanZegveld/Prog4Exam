#pragma once
#include "Singleton.h"

class ColliderComponent;
class GameObject;

class ColliderManager final : public Singleton<ColliderManager>
{
public:
	ColliderManager();
	~ColliderManager();

	void Update(float deltaTime);

	void AddDynamic(std::shared_ptr<ColliderComponent> col) { mDynamicColliders.push_back(col); }
	void AddStatic(std::shared_ptr<ColliderComponent> col) { mStaticColliders.push_back(col); }
	void AddTrigger(std::shared_ptr<ColliderComponent> col) { mTriggerColliders.push_back(col); }

	bool CheckCollision(std::shared_ptr<GameObject> gameObj); //True if nothing is hit

private:

	std::vector<std::shared_ptr<ColliderComponent>> mDynamicColliders;
	std::vector<std::shared_ptr<ColliderComponent>> mStaticColliders;
	std::vector<std::shared_ptr<ColliderComponent>> mTriggerColliders;
};

