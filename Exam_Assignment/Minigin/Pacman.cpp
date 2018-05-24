#include "MiniginPCH.h"
#include "Pacman.h"
#include "Components.h"
#include "ColliderManager.h"
#include "Wall.h"
#include "PickUp.h"
#include "Scene.h"


Pacman::Pacman() : mColliderManager(ColliderManager::GetInstance())
{

}


Pacman::~Pacman()
{
}

void Pacman::Init()
{
	//	Attaching Transform from original GameObject
	GameObject::Init();

	auto rend = std::make_shared<RenderComponent>();
	AddComponent(rend);
	auto textComp = std::make_shared<TextureComponent>();
	AddComponent(textComp);
	textComp->SetTexture("pacman.png");
	auto colComp = std::make_shared<ColliderComponent>(GetTransform()->GetPosition(), (float)rend->GetTextureSize().width, (float)rend->GetTextureSize().height, ColliderType::DYNAMIC);
	AddComponent(colComp);
}

void Pacman::Update(float deltaTime)
{
	//	Update all the components first
	GameObject::Update(deltaTime);

	auto speed = GetSpeed() * deltaTime;
	//auto offset = speed * 3.f;

	switch (mCurrentDir)
	{
	case Direction::UP:
		GetTransform()->Move(0, -speed);
		break;
	case Direction::LEFT:
		GetTransform()->Move(-speed, 0);
		break;
	case Direction::RIGHT:
		GetTransform()->Move(speed, 0);
		break;
	case Direction::DOWN:
		GetTransform()->Move(0, speed);
		break;
	case Direction::NONE:
		GetTransform()->Move(0, 0);
		break;
	default:
		break;
	}

	//CheckCollisionInDirection makes sure we behave correctly when hitting walls
	if (!CheckCollisionInDirection(mNextDir, deltaTime,5.f))
		SetDirection(mNextDir);

	if(CheckCollisionInDirection(mCurrentDir,deltaTime,1.f))
		SetDirection(Direction::NONE);

	if(mColliderManager.CheckCollision(shared_from_this()))
	{
		auto collider = mColliderManager.GetCollider();
		auto obj = collider->GetGameObject();
		//Check for 3 casts;
		//	Miss Pacman ; Ghosts ; PickUps
		auto pacCast = std::dynamic_pointer_cast<Pacman>(obj.lock());
		{}

		auto pickCast = std::dynamic_pointer_cast<PickUp>(obj.lock());
		if (pickCast)
		{
			//	Pickup;
			mToDestroy.push_back(obj.lock());
			mScore++;
		}
	}


	//if(mColliderManager.CheckCollision(shared_from_this()))
	//{
	//	auto collider = mColliderManager.GetCollider();
	//	auto obj = collider->GetGameObject();
	//	//	Check for 3 casts; Ghost/Pickup/Wall
	//	//	Wall
	//	auto wallCast = std::dynamic_pointer_cast<Wall>(obj.lock());
	//	if(wallCast)
	//	{
	//		//	Bumped into wall; do logic
	//		switch (mCurrentDir)
	//		{
	//		case Direction::UP:
	//			GetTransform()->Move(0, speed + offset);
	//			break;
	//		case Direction::LEFT:
	//			GetTransform()->Move(speed + offset, 0);;
	//			break;
	//		case Direction::RIGHT:
	//			GetTransform()->Move(-(speed + offset), 0);
	//			break;
	//		case Direction::DOWN:
	//			GetTransform()->Move(0, -(speed + offset));
	//			break;
	//		case Direction::NONE:
	//			GetTransform()->Move(0, 0);
	//			break;
	//		default:
	//			break;
	//		}
	//		SetDirection(Direction::NONE);

	//	}

	//	//	PickUp
	//	auto pickCast = std::dynamic_pointer_cast<PickUp>(obj.lock());
	//	if(pickCast)
	//	{
	//		//	Pickup;
	//		mToDestroy.push_back(obj.lock());
	//		mScore++;
	//	}
	//}
}

bool Pacman::CheckCollisionInDirection(Direction dir,float deltaTime, float unitTest)
{
	float testUnit = unitTest;
	switch (dir)
	{
	case Direction::UP:
		GetTransform()->Move(0.0f, -testUnit);
		break;
	case Direction::LEFT:
		GetTransform()->Move(-testUnit, 0.f);
		break;
	case Direction::RIGHT:
		GetTransform()->Move(testUnit, 0.f);
		break;
	case Direction::DOWN:
		GetTransform()->Move(0.0f, testUnit);
		break;
	case Direction::NONE:
		return false;
	}
	for(auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
	auto hit = mColliderManager.CheckCollision(shared_from_this());

	switch (dir)
	{
	case Direction::UP:
		GetTransform()->Move(0.0f, testUnit);
		break;
	case Direction::LEFT:
		GetTransform()->Move(testUnit, 0.f);
		break;
	case Direction::RIGHT:
		GetTransform()->Move(-testUnit, 0.f);
		break;
	case Direction::DOWN:
		GetTransform()->Move(0.0f, -testUnit);
		break;
	case Direction::NONE:
		break;
	}
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
	// Making sure this only returns true if the hit object is a wall object;
	//	We are currently only using this function to behave correctly with walls;
	return hit && std::dynamic_pointer_cast<Wall>(mColliderManager.GetCollider()->GetGameObject().lock());
}
