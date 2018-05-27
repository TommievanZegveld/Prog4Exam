#include "MiniginPCH.h"
#include "Teleporter.h"
#include "Components.h"
#include "ColliderManager.h"
#include "Character.h"


Teleporter::Teleporter(glm::vec2 pos1, Direction dir, glm::vec2 pos2) : mPosition(pos1),mToPosition(pos2), mAllowDirection(dir),mColliderManager(ColliderManager::GetInstance())
{
}


Teleporter::~Teleporter()
{
}

void Teleporter::Init()
{
	//	Attaching Transform from original GameObject
	GameObject::Init();

	SetPosition(mPosition.x, mPosition.y);
	auto collider = std::make_shared<ColliderComponent>(glm::vec2(mPosition.x, mPosition.y), 24.f, 24.f, ColliderType::DYNAMIC);
	AddComponent(collider);
	//	Make Teleporter visible with a green color
	//auto rect = std::make_shared<RectangleComponent>(24.f, 24.f, Color{ 0,255,0 });
	//AddComponent(rect);
}

void Teleporter::Update(float deltaTime)
{
	//	Update all the components first
	GameObject::Update(deltaTime);
	UNREFERENCED_PARAMETER(deltaTime);

	if (mColliderManager.CheckCollision(shared_from_this()))
	{
		auto collidingObj = mColliderManager.GetCollider()->GetGameObject().lock();
		auto charCast = std::dynamic_pointer_cast<Character>(collidingObj);
		if (charCast)
		{
			if (charCast->GetDirection() == mAllowDirection)
				collidingObj->GetTransform()->SetPosition(mToPosition.x, mToPosition.y);
		}
	}	
}

