#include "MiniginPCH.h"
#include "Pacman.h"
#include "Components.h"
#include "ColliderManager.h"
#include "Wall.h"
#include "PickUp.h"
#include "Ghost.h"
#include "Scene.h"
#include "SpecialPickUp.h"


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

	if (mLives <= 0)
	{	
		SetPosition(510, 220);
		return;
	}

	auto speed = GetSpeed() * deltaTime;
	//auto offset = speed * 3.f;

	if (mSuperState)
	{
		if (mSuperTimer >= mSuperTime)
		{	
			mSuperState = false;
			mSuperTimer = 0.0f;
			SetSpeed(100.f);
			return;
		}
		
		mSuperTimer += deltaTime;
		SetSpeed(150.f);
	}

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

	if(CheckCollisionInDirection(mCurrentDir,deltaTime, 2.f))
		SetDirection(Direction::NONE);

	if(mColliderManager.CheckCollision(shared_from_this()))
	{
		auto collider = mColliderManager.GetCollider();
		auto obj = collider->GetGameObject();
		//Check for 3 casts;
		//	Miss Pacman ; Ghosts ; PickUps
		auto ghostCast = std::dynamic_pointer_cast<Ghost>(obj.lock());
		if(ghostCast)
		{
			if(mSuperState)
			{
				mScore += 100;
				auto spawnpoints = ghostCast->GetSpawnPoints();
				int randIdx = rand() % 4;
				auto spawnpoint = spawnpoints[randIdx];
				ghostCast->SetPosition(spawnpoint.x,spawnpoint.y);
			}
			else
			{
				shared_from_this()->SetPosition(mSpawnPoint.x, mSpawnPoint.y);
				mLives -= 1;
				SetDirection(Direction::NONE);
				SetNextDirection(Direction::NONE);
			}
		}

		auto pickCast = std::dynamic_pointer_cast<PickUp>(obj.lock());
		if (pickCast)
		{
			//	Pickup;
			mToDestroy.push_back(obj.lock());
			mScore += pickCast->GetScore();
			if (std::dynamic_pointer_cast<SpecialPickUp>(pickCast))
			{
				mSuperState = true;
				// Reset timer when a new super pickup has been picked up
				mSuperTimer = 0.0f;
			}
		}
	}
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
