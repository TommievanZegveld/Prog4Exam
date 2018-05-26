#include "MiniginPCH.h"
#include "Teleporter.h"
#include "Components.h"
#include "ColliderManager.h"
#include "Character.h"


Teleporter::Teleporter(glm::vec2 pos1, Direction dir, glm::vec2 pos2, Direction dir2) : mPosition1(pos1),mPosition2(pos2),mDirection1(dir),mDirection2(dir2), mColliderManager(ColliderManager::GetInstance())
{
}


Teleporter::~Teleporter()
{
}

void Teleporter::Init()
{
	mPortal1 = std::make_shared<GameObject>();
	mPortal2 = std::make_shared<GameObject>();

	mPortal1->Init();
	mPortal2->Init();

	mPortal1->GetTransform()->SetPosition(mPosition1.x, mPosition1.y);
	auto collider = std::make_shared<ColliderComponent>(glm::vec2(mPosition1.x, mPosition1.y), 24.f, 24.f, ColliderType::STATIC);
	mPortal1->AddComponent(collider);

	mPortal2->GetTransform()->SetPosition(mPosition2.x, mPosition2.y);
	auto collider2 = std::make_shared<ColliderComponent>(glm::vec2(mPosition2.x, mPosition2.y), 24.f, 24.f, ColliderType::STATIC);
	mPortal2->AddComponent(collider);
}

void Teleporter::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (mColliderManager.CheckCollision(mPortal1))
	{
		auto collidingObj = mColliderManager.GetCollider()->GetGameObject().lock();
		auto charCast = std::dynamic_pointer_cast<Character>(collidingObj);
		if (charCast)
		{
			if (charCast->GetDirection() == mDirection1)
				collidingObj->GetTransform()->SetPosition(mPosition2.x, mPosition2.y);
		}
	}

	if (mColliderManager.CheckCollision(mPortal2))
	{
		auto collidingObj = mColliderManager.GetCollider()->GetGameObject().lock();
		auto charCast = std::dynamic_pointer_cast<Character>(collidingObj);
		if (charCast)
		{
			if (charCast->GetDirection() == mDirection2)
				collidingObj->GetTransform()->SetPosition(mPosition1.x, mPosition1.y);
		}
	}
	
}

