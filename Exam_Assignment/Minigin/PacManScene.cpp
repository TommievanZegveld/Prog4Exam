#include "MiniginPCH.h"
#include "PacManScene.h"
#include "Scene.h"
#include "Components.h"
#include "Character.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameCommands.h"
#include "ColliderManager.h"

#include "Pacman.h"
#include "Wall.h"
#include "GameObject.h"
#include "PickUp.h"
#include <algorithm>

PacManScene::PacManScene() : Scene("Pacman Scene")
{
}


PacManScene::~PacManScene()
{
}

void PacManScene::Initialize()
{
	//	Input Bindings for Pacman;
	auto& input = InputManager::GetInstance();
	//	Input Setters
	//		Commands
	auto upCommand = std::make_shared<UpCommand>();
	auto downCommand = std::make_shared<DownCommand>();
	auto leftCommand = std::make_shared<LeftCommand>();
	auto rightCommand = std::make_shared<RightCommand>();

	//	Bindings
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonY, upCommand);
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonA, downCommand);
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonX, leftCommand);
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonB, rightCommand);

	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonY, upCommand);
	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonA, downCommand);
	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonX, leftCommand);
	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonB, rightCommand);

	// Keyboard Player 1
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_W, upCommand);
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_A, leftCommand);
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_S, downCommand);
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_D, rightCommand);
	//	Keyboard Player 2
	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_UP, upCommand);
	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_DOWN, downCommand);
	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_LEFT, leftCommand);
	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_RIGHT, rightCommand);

	auto go4 = std::make_shared<GameObject>();
	Add(go4);
	auto rendComp = std::make_shared<RenderComponent>();
	go4->AddComponent(rendComp);
	auto fpsComp = std::make_shared<FPSComponent>();
	go4->AddComponent(fpsComp);
	go4->SetPosition(100, 40);

	auto player1 = std::make_shared<Pacman>();
	Add(player1);
	mActivePlayers.push_back(player1);

	//auto player2 = std::make_shared<Pacman>()->GetPacmanObject();
	//Add(player2);
	//mActivePlayers.push_back(player2);

	auto wall1 = std::make_shared<Wall>(glm::vec2(300, 300), 200, 20);
	Add(wall1);


	auto pickup1 = std::make_shared<PickUp>(glm::vec2(250, 250));
	Add(pickup1);

	//auto wall = std::make_shared<GameObject>();
	//auto rend = std::make_shared<RenderComponent>();
	//wall->AddComponent(rend);
	//auto text = std::make_shared<TextureComponent>();
	//wall->AddComponent(text);
	//text->SetTexture("red.png");
	//wall->SetPosition(160, 160);
	//wall->AddComponent(std::make_shared<ColliderComponent>(wall->GetTransform()->GetPosition(), (float)rend->GetTextureSize().width, (float)rend->GetTextureSize().height, ColliderType::STATIC));
	////Add(wall);

	input.SetPlayer(GameController::Controller1, mActivePlayers[0]);
	//input.SetPlayer(GameController::KeyBoard2, mActivePlayers[1]);
}

void PacManScene::Update(float deltaTime)
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}

	auto& collision = ColliderManager::GetInstance();

	for (auto character : mActivePlayers)
	{
		auto dir = character->GetDirection();
		auto speed = 100.f * deltaTime;
		auto offset = speed * 10.f;

		switch (dir)
		{
		case Direction::UP:
			character->GetTransform()->Move(0, -speed);
			break;
		case Direction::LEFT:
			character->GetTransform()->Move(-speed, 0);
			break;
		case Direction::RIGHT:
			character->GetTransform()->Move(speed, 0);
			break;
		case Direction::DOWN:
			character->GetTransform()->Move(0, speed);
			break;
		case Direction::NONE:
			character->GetTransform()->Move(0, 0);
			break;
		default:
			break;
		}

		if (collision.CheckCollision(character))
		{
			switch (dir)
			{
			case Direction::UP:
				character->GetTransform()->Move(0, speed + offset);
				break;
			case Direction::LEFT:
				character->GetTransform()->Move(speed + offset, 0);
				break;
			case Direction::RIGHT:
				character->GetTransform()->Move(-(speed + offset), 0);
				break;
			case Direction::DOWN:
				character->GetTransform()->Move(0, -(speed + offset));
				break;
			default:
				break;
			}

			auto collider = collision.GetCollider();
			auto obj = collider->GetGameObject();
			auto dynCast = std::dynamic_pointer_cast<Wall>(obj.lock());

			if(dynCast)
			{
				std::cout << "WALL" << std::endl;
				character->SetDirection(Direction::NONE);
			}

			auto dynCast2 = std::dynamic_pointer_cast<PickUp>(obj.lock());
			if(dynCast2)
			{
				for (size_t i = 0; i < mObjects.size(); i++)
				{
					if (obj.lock() == mObjects[i])
						mToDelete.push_back(mObjects[i]);
				}
				std::cout << "PICKUP BABY" << std::endl;
			}
		}
	}

	DestroyObjects();
}



