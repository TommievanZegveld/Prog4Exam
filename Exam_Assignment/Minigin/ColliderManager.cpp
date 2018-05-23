#include "MiniginPCH.h"
#include "ColliderManager.h"
#include "ColliderComponent.h"
#include "GameObject.h"

#include <algorithm>

ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}

void ColliderManager::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void ColliderManager::RemoveCollider(std::shared_ptr<GameObject> obj)
{
	UNREFERENCED_PARAMETER(obj);
	auto col = obj->GetComponent<ColliderComponent>();

	if (std::find(mDynamicColliders.begin(), mDynamicColliders.end(), col) != mDynamicColliders.end())
	{
		mDynamicColliders.erase(std::remove(mDynamicColliders.begin(), mDynamicColliders.end(), col));
	}

	if (std::find(mStaticColliders.begin(), mStaticColliders.end(), col) != mStaticColliders.end())
	{
		mStaticColliders.erase(std::remove(mStaticColliders.begin(), mStaticColliders.end(), col));
	}

	if (std::find(mTriggerColliders.begin(), mTriggerColliders.end(), col) != mTriggerColliders.end())
	{
		mTriggerColliders.erase(std::remove(mTriggerColliders.begin(), mTriggerColliders.end(), col));
	}
}

bool ColliderManager::CheckCollision(std::shared_ptr<GameObject> gameObj) 
{
	for (auto stat : mStaticColliders)
	{
		auto hit = gameObj->GetComponent<ColliderComponent>()->isColliding(*stat);
		if (hit)
		{
			mCollider = stat;
			return hit;
		}
	}
	for (auto dyn : mDynamicColliders)
	{
		//	Don't check collision with self
		if (dyn != gameObj->GetComponent<ColliderComponent>())
		{
			auto hit = gameObj->GetComponent<ColliderComponent>()->isColliding(*dyn);
			if (hit)
			{	
				mCollider = dyn;
				return hit;
			}
		}
	}
	return false;
}

std::shared_ptr<ColliderComponent> ColliderManager::GetCollider()
{
	return mCollider;
}
