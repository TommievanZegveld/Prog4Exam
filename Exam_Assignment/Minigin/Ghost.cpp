#include "MiniginPCH.h"
#include "Ghost.h"
#include "Components.h"
#include "ColliderManager.h"
#include "Wall.h"
#pragma warning (disable:4244)
#include <time.h>
#include <chrono>


Ghost::Ghost() : mColliderManager(ColliderManager::GetInstance())
{
}

Ghost::~Ghost()
{
}

void Ghost::Init()
{
	//	Attaching Transform from original GameObject
	GameObject::Init();

	auto rend = std::make_shared<RenderComponent>();
	AddComponent(rend);
	auto textComp = std::make_shared<TextureComponent>();
	AddComponent(textComp);
	textComp->SetTexture("ghost.png");
	auto colComp = std::make_shared<ColliderComponent>(GetTransform()->GetPosition(), (float)rend->GetTextureSize().width, (float)rend->GetTextureSize().height, ColliderType::DYNAMIC);
	AddComponent(colComp);
	//	Pacman runs at 100.f units; so ghosts go a bit faster;
	SetSpeed(110.f);
	mNextDir = Direction::NONE;
}

void Ghost::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	auto speed = GetSpeed() * deltaTime;

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

	auto then1 = std::chrono::high_resolution_clock::now();

	//CheckCollisionInDirection makes sure we behave correctly when hitting walls
	if (!CheckCollisionInDirection(mNextDir, deltaTime, 5.f))
	{
		//	Not Colliding with mNextDir
		SetDirection(mNextDir);
	}

	if (CheckCollisionInDirection(mCurrentDir, deltaTime, 2.f))
	{
		SetDirection(Direction::NONE);
	}
	auto now1 = std::chrono::high_resolution_clock::now();
	auto seed = std::chrono::duration_cast<std::chrono::microseconds>(now1 - then1);
	srand(seed.count());
	mNextDirectionTimer += deltaTime;
	if(mNextDirectionTimer >= 1.f && !mPlayerControlled)
	{	
		SetNextDirection(Direction(rand() % 4));
		mNextDirectionTimer = 0.0f;
	}
}

bool Ghost::CheckCollisionInDirection(Direction dir, float deltaTime, float unitTest)
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
	for (auto comp : mComponents)
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