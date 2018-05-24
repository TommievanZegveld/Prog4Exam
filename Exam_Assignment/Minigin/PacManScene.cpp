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
#include "LevelLoader.h"

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

	auto level = std::make_shared<LevelLoader>("level.csv");
	auto walls = level->GetWalls();
	for (auto wall : walls)
		Add(wall);
	auto pickups = level->GetPickUps();
	for (auto pick : pickups)
		Add(pick);

	auto go4 = std::make_shared<GameObject>();
	Add(go4);
	auto rendComp = std::make_shared<RenderComponent>();
	go4->AddComponent(rendComp);
	auto fpsComp = std::make_shared<FPSComponent>();
	go4->AddComponent(fpsComp);
	go4->SetPosition(550, 440);

	auto player1 = std::make_shared<Pacman>();
	Add(player1);
	player1->SetPosition(224, 266);
	mActivePlayers.push_back(player1);

	auto scoreObj = std::make_shared<GameObject>();
	Add(scoreObj);
	scoreObj->AddComponent(std::make_shared<RenderComponent>());
	auto textComp = std::make_shared<TextComponent>("Score: 0", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), Color{ 255, 255, 255 });
	scoreObj->AddComponent(textComp);

	scoreObj->SetPosition(550, 30);
	mScoreObjects.push_back(scoreObj);

	auto player2 = std::make_shared<Pacman>();
	Add(player2);
	player2->SetPosition(224, 174);
	mActivePlayers.push_back(player2);

	auto scoreObj2 = std::make_shared<GameObject>();
	Add(scoreObj2);
	scoreObj2->AddComponent(std::make_shared<RenderComponent>());
	auto textComp2 = std::make_shared<TextComponent>("Score: 0", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), Color{ 255, 255, 255 });
	scoreObj2->AddComponent(textComp2);
	scoreObj2->SetPosition(550, 130);
	mScoreObjects.push_back(scoreObj2);

	input.SetPlayer(GameController::KeyBoard1, mActivePlayers[0]);
	input.SetPlayer(GameController::KeyBoard2, mActivePlayers[1]);
}

void PacManScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	// Ask Pacman object what collided objects to destroy;
	//	If it hits a pickup for example; it flags it in it's update for destruction
	for (size_t i = 0; i < mActivePlayers.size(); i++)
	{
		auto score = 0;
		auto pacManCast = std::dynamic_pointer_cast<Pacman>(mActivePlayers[i]);
		if (pacManCast)
		{
			auto toDestroy = pacManCast->GetDestroyFlaggedActor();
			for (auto des : toDestroy)
				FlagForDestruction(des);
			score = pacManCast->GetScore();
		}
		auto text = "Score: " + std::to_string(score);
		mScoreObjects[i]->GetComponent<TextComponent>()->SetText(text);
	}

	DestroyObjects();
}



