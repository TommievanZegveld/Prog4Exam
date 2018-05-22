#include "MiniginPCH.h"
#include "PacManScene.h"
#include "Scene.h"
#include "Components.h"
#include "Character.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameCommands.h"

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
	auto fpsComp = std::make_shared<FPSComponent>();
	auto rendComp = std::make_shared<RenderComponent>();
	go4->AddComponent(rendComp);
	go4->AddComponent(fpsComp);
	go4->SetPosition(10, 10);
	Add(go4);

	auto player1 = std::make_shared<Character>();
	auto rendCompp = std::make_shared<RenderComponent>();
	player1->AddComponent(std::make_shared<RenderComponent>());
	auto textComp = std::make_shared<TextureComponent>();
	player1->AddComponent(textComp);
	textComp->SetTexture("pacman.png");
	Add(player1);
	mActivePlayers.push_back(player1);

	auto player2 = std::make_shared<Character>();
	player2->AddComponent(std::make_shared<RenderComponent>());
	auto textComp2 = std::make_shared<TextureComponent>();
	player2->AddComponent(textComp2);
	textComp2->SetTexture("pacman.png");
	auto colComp = std::make_shared<ColliderComponent>(ColliderType::DYNAMIC,52,52);
	Add(player2);
	mActivePlayers.push_back(player2);

	input.SetPlayer(GameController::Controller1, mActivePlayers[0]);
	input.SetPlayer(GameController::Controller2, mActivePlayers[1]);
}

void PacManScene::Update(float deltaTime)
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update(deltaTime);
	}

	for (auto character : mActivePlayers)
	{
		auto dir = character->GetDirection();
		auto speed = 100.f * deltaTime;
		switch (dir)
		{
		case Direction::UP:
			character->GetTransform()->Move(0, -speed, 0);
			break;
		case Direction::LEFT:
			character->GetTransform()->Move(-speed, 0, 0);
			break;
		case Direction::RIGHT:
			character->GetTransform()->Move(speed, 0, 0);
			break;
		case Direction::DOWN:
			character->GetTransform()->Move(0, speed, 0);
			break;
		case Direction::NONE:
			character->GetTransform()->Move(0, 0, 0);
			break;
		default:
			break;
		}
	}
}



