#include "MiniginPCH.h"
#include "ColliderManager.h"
#include "ColliderComponent.h"
#include "GameObject.h"

ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}

void ColliderManager::Update(float deltaTime)
{

}

bool ColliderManager::CheckCollision(std::shared_ptr<GameObject> gameObj) 
{
	for(auto dyn : mDynamicColliders)
	{
		for(auto stat :  mStaticColliders)
		{
				
		}
	}
}
