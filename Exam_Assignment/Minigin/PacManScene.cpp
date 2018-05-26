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
#include "Ghost.h"
#include "Wall.h"
#include "GameObject.h"
#include "PickUp.h"
#include "SpecialPickUp.h"
#include <algorithm>
#include "LevelLoader.h"
#include "GameTypes.h"
#include "GameSettings.h"
#include "Teleporter.h"

PacManScene::PacManScene() : Scene("Pacman Scene")
{
}


PacManScene::~PacManScene()
{
}

void PacManScene::Initialize()
{
	//	Input Bindings
	auto& input = InputManager::GetInstance();
	//	Input Setters
	//		Commands
	auto upCommand = std::make_shared<UpCommand>();
	auto downCommand = std::make_shared<DownCommand>();
	auto leftCommand = std::make_shared<LeftCommand>();
	auto rightCommand = std::make_shared<RightCommand>();

	//	Bindings
	//	Controllers
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonY, upCommand);
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonA, downCommand);
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonX, leftCommand);
	input.BindControllerKey(GameController::Controller1, ControllerButton::ButtonB, rightCommand);

	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonY, upCommand);
	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonA, downCommand);
	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonX, leftCommand);
	input.BindControllerKey(GameController::Controller2, ControllerButton::ButtonB, rightCommand);

	//	Keyboards
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_W, upCommand);
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_A, leftCommand);
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_S, downCommand);
	input.BindKeyboardKey(GameController::KeyBoard1, SDL_SCANCODE_D, rightCommand);

	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_UP, upCommand);
	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_DOWN, downCommand);
	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_LEFT, leftCommand);
	input.BindKeyboardKey(GameController::KeyBoard2, SDL_SCANCODE_RIGHT, rightCommand);

	//	Level
	auto level = std::make_shared<LevelLoader>("level.csv");
	auto walls = level->GetWalls();
	for (auto wall : walls)
		Add(wall);
	auto pickups = level->GetPickUps();
	for (auto pick : pickups)
		Add(pick);
	auto specials = level->GetSpecials();
	for (auto spec : specials)
		Add(spec);
	auto portals = level->GetPortals();
	for (auto portal : portals)
	{
		Add(portal);
		Add(portal->mPortal1);
		Add(portal->mPortal2);
	}

	//	FPS-Counter
	auto go4 = std::make_shared<GameObject>();
	Add(go4);
	auto rendComp = std::make_shared<RenderComponent>();
	go4->AddComponent(rendComp);
	auto fpsComp = std::make_shared<FPSComponent>();
	go4->AddComponent(fpsComp);
	go4->SetPosition(550, 440);

	//Load Settings from selection screen
	auto settings = GameSettings::GetInstance().LoadSettings();

	for(auto setting : settings)
	{
		if (setting.player == Player::GHOST && mGhostCounter < mMaxGhosts)
		{
			auto ghost = std::make_shared<Ghost>();
			Add(ghost);
			ghost->SetPosition(ghost->GetSpawnPoints()[mGhostCounter].x, ghost->GetSpawnPoints()[mGhostCounter].y);
			ghost->SetPlayerControlled(true);
			mActivePlayers.push_back(ghost);
			if (setting.controller == Controller::KEYBOARD && mKeyBoardCounter < mMaxKeyboard)
			{
				input.SetPlayer(GameController(mKeyBoardCounter + 4), mActivePlayers[mPlayerCounter]);
				mKeyBoardCounter++;
			}
			else if (setting.controller == Controller::CONTROLLER && mControllerCounter < mMaxController)
			{
				input.SetPlayer(GameController(mControllerCounter), mActivePlayers[mPlayerCounter]);
				mControllerCounter++;
			}
			mGhostCounter++;
			mPlayerCounter++;
		}
		else if(setting.player == Player::PACMAN && mPacmanCounter < mMaxPacman)
		{
			auto pacman = std::make_shared<Pacman>();
			Add(pacman);
			pacman->SetPosition(pacman->GetSpawnPoint().x, pacman->GetSpawnPoint().y);
			mActivePlayers.push_back(pacman);
			auto scoreObj = std::make_shared<GameObject>();
			Add(scoreObj);
			scoreObj->AddComponent(std::make_shared<RenderComponent>());
			auto textComp = std::make_shared<TextComponent>("Score: 0", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), Color{ 255, 255, 255 });
			scoreObj->AddComponent(textComp);
			scoreObj->SetPosition(550, 30 + (mPacmanCounter*100.f));
			mScoreObjects.push_back(scoreObj);

			if(setting.controller == Controller::KEYBOARD && mKeyBoardCounter < mMaxKeyboard)
			{
				input.SetPlayer(GameController(mKeyBoardCounter + 4), mActivePlayers[mPlayerCounter]);
				mKeyBoardCounter++;
			}
			else if (setting.controller == Controller::CONTROLLER && mControllerCounter < mMaxController)
			{
				input.SetPlayer(GameController(mControllerCounter), mActivePlayers[mPlayerCounter]);
				mControllerCounter++;
			}
			mPacmanCounter++;
			mPlayerCounter++;
		}
	}

	for (size_t i = mGhostCounter; i < mMaxGhosts; i++)
	{
		auto ghost = std::make_shared<Ghost>();
		Add(ghost);
		ghost->SetPosition(ghost->GetSpawnPoints()[i].x, ghost->GetSpawnPoints()[i].y);
	}

	////	Pacman 1 Object
	//auto pacman1 = std::make_shared<Pacman>();
	//Add(pacman1);
	//pacman1->SetPosition(pacman1->GetSpawnPoint().x, pacman1->GetSpawnPoint().y);
	////	Score for Pacman 1
	//auto scoreObj = std::make_shared<GameObject>();
	//Add(scoreObj);
	//scoreObj->AddComponent(std::make_shared<RenderComponent>());
	//auto textComp = std::make_shared<TextComponent>("Score: 0", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), Color{ 255, 255, 255 });
	//scoreObj->AddComponent(textComp);
	//scoreObj->SetPosition(550, 30);
	//mScoreObjects.push_back(scoreObj);
	//////	Pacman 2 Object
	////auto pacman2 = std::make_shared<Pacman>();
	////Add(pacman2);
	////pacman2->SetPosition(pacman2->GetSpawnPoint().x, pacman2->GetSpawnPoint().y);
	//////	Score for Pacman 2
	////auto scoreObj2 = std::make_shared<GameObject>();
	////Add(scoreObj2);
	////scoreObj2->AddComponent(std::make_shared<RenderComponent>());
	////auto textComp2 = std::make_shared<TextComponent>("Score: 0", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), Color{ 255, 255, 255 });
	////scoreObj2->AddComponent(textComp2);
	////scoreObj2->SetPosition(550, 130);
	////mScoreObjects.push_back(scoreObj2);
	////	Ghost 1
	//auto ghost1 = std::make_shared<Ghost>();
	//Add(ghost1);
	//ghost1->SetPosition(ghost1->GetSpawnPoints()[0].x, ghost1->GetSpawnPoints()[0].y);
	////	Ghost 2
	//auto ghost2 = std::make_shared<Ghost>();
	//Add(ghost2);
	//ghost2->SetPosition(ghost1->GetSpawnPoints()[1].x, ghost1->GetSpawnPoints()[1].y);
	////	Ghost 3
	//auto ghost3 = std::make_shared<Ghost>();
	//Add(ghost3);
	//ghost3->SetPosition(ghost1->GetSpawnPoints()[2].x, ghost1->GetSpawnPoints()[2].y);
	//	Ghost 4
	//auto ghost4 = std::make_shared<Ghost>();
	//Add(ghost4);
	//ghost4->SetPosition(ghost4->GetSpawnPoints()[3].x, ghost4->GetSpawnPoints()[3].y);



	//mActivePlayers.push_back(ghost1); ghost1->SetPlayerControlled(true);
	//mActivePlayers.push_back(pacman1);

	//input.SetPlayer(GameController::KeyBoard1, mActivePlayers[0]);
	//input.SetPlayer(GameController::KeyBoard2, mActivePlayers[1]);
}

void PacManScene::DestroyLocals()
{
	mActivePlayers.clear();
	mScoreObjects.clear();
	mKeyBoardCounter = 0;
	mControllerCounter = 0;
	mPlayerCounter = 0;
	mGhostCounter = 0;
	mPacmanCounter = 0;
}

void PacManScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	// Ask Pacman object what collided objects to destroy;
	//	If it hits a pickup for example; it flags it in it's update for destruction
	auto scoreIt = 0;
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
			auto text = "Score: " + std::to_string(score);
			mScoreObjects[scoreIt]->GetComponent<TextComponent>()->SetText(text);
			scoreIt++;
		}
	}

	DestroyObjects();
}



