#include "MiniginPCH.h"
#include "SelectionScene.h"
#include "LevelLoader.h"
#include "Wall.h"
#include "PickUp.h"
#include "SpecialPickUp.h"


SelectionScene::SelectionScene() : Scene("Selection Scene")
{
}


SelectionScene::~SelectionScene()
{
}

void SelectionScene::Initialize()
{
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
}

void SelectionScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}


