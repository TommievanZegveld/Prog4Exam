#include "MiniginPCH.h"
#include "SelectionScene.h"
#include "LevelLoader.h"
#include "Wall.h"
#include "PickUp.h"
#include "SpecialPickUp.h"
#include "Components.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameSettings.h"


SelectionScene::SelectionScene() : Scene("Selection Scene"), mInputManager(InputManager::GetInstance())
{
}


SelectionScene::~SelectionScene()
{
}

void SelectionScene::Initialize()
{
	// Filling the selections with the options
	//mPlayerSettingSelection[0] = mOptions[0];


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto color = Color{ 255,255,255 };

	float startY = 100.f;
	auto playerID = 1;
	for(auto& player : mPlayerAndSettings)
	{
		auto player_Setting = std::make_shared<GameObject>();
		Add(player_Setting);
		player_Setting->AddComponent(std::make_shared<RenderComponent>());
		player_Setting->AddComponent(std::make_shared<TextComponent>("Player" + std::to_string(playerID) + " :" + mOptions[0] + " " + mControllerOptions[0], font, color));
		player_Setting->SetPosition(320, startY);
		startY += 100.f;
		playerID++;
		player.first = player_Setting;
	}
	mCurrentlyActiveObject = mPlayerAndSettings[0].first;
	mCurrentChoice = 0;
}

std::string SelectionScene::PlayerToString(Player p)
{
	if (p == Player::GHOST)
		return "Ghost";
	if (p == Player::PACMAN)
		return "Pacman";
	if (p == Player::NONE)
		return "No Player";
	return "ERROR";
}

std::string SelectionScene::ControllerToString(Controller c)
{
	if (c == Controller::CONTROLLER)
		return "Controller";
	if (c == Controller::KEYBOARD)
		return "Keyboard";
	return "ERROR";
}

void SelectionScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		mPlayerAndSettings[i].first->GetComponent<TextComponent>()->SetText(
			"Player" + std::to_string(i + 1) + " :" +
			PlayerToString(mPlayerAndSettings[i].second.player) + " " +
			ControllerToString(mPlayerAndSettings[i].second.controller));
	}

	if(mInputManager.IsPressed(SDL_SCANCODE_RIGHT))
	{
		for(auto& obj : mPlayerAndSettings)
		{
			if (obj.first == mCurrentlyActiveObject)
			{
				if(mCurrentChoice == 1)
				{
					obj.second.controller = Controller((int(obj.second.controller) + 1) % mControllerChoices);
				}
				else
				{
					obj.second.player = Player((int(obj.second.player) + 1) % mOptionChoices);
				}
			}
		}
	}

	if (mInputManager.IsPressed(SDL_SCANCODE_SPACE))
		mCurrentChoice = (mCurrentChoice + 1) % 2;

	if(mInputManager.IsPressed(SDL_SCANCODE_DOWN))
		for (size_t i = 0; i < MAX_PLAYERS; i++)
		{
			if (mPlayerAndSettings[i].first == mCurrentlyActiveObject)
			{
				mCurrentlyActiveObject = mPlayerAndSettings[++i % MAX_PLAYERS].first;
				mCurrentChoice = 0;
			}
		}

	GameSettings::GetInstance().SaveSettings(
		mPlayerAndSettings[0].second, mPlayerAndSettings[1].second, mPlayerAndSettings[2].second, mPlayerAndSettings[3].second);
}


