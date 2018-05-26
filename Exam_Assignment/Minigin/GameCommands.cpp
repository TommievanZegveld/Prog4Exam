#include "MiniginPCH.h"
#include "GameCommands.h"
#include "Character.h"
#include "SceneManager.h"

void UpCommand::execute(std::weak_ptr<GameObject>& gameObj)
{
	auto character = std::dynamic_pointer_cast<Character>(gameObj.lock());
	if(character)
	{	
		character->SetNextDirection(Direction::UP);
		//std::cout << "Up command pressed" << std::endl;
	}
}

void DownCommand::execute(std::weak_ptr<GameObject>& gameObj)
{
	auto character = std::dynamic_pointer_cast<Character>(gameObj.lock());
	if (character)
	{
		character->SetNextDirection(Direction::DOWN);
		//std::cout << "Down command pressed" << std::endl;
	}
}

void LeftCommand::execute(std::weak_ptr<GameObject>& gameObj)
{
	auto character = std::dynamic_pointer_cast<Character>(gameObj.lock());
	if (character)
	{
		character->SetNextDirection(Direction::LEFT);
		//std::cout << "Left command pressed" << std::endl;
	}
}

void RightCommand::execute(std::weak_ptr<GameObject>& gameObj)
{
	auto character = std::dynamic_pointer_cast<Character>(gameObj.lock());
	if (character)
	{
		character->SetNextDirection(Direction::RIGHT);
		//std::cout << "Right command pressed" << std::endl;
	}
}

void NextCommand::execute(std::weak_ptr<GameObject>& gameObj)
{
	UNREFERENCED_PARAMETER(gameObj);
	auto& sceneManager = ::SceneManager::GetInstance();
	sceneManager.NextScene();
}

void PreviousCommand::execute(std::weak_ptr<GameObject>& gameObj)
{
	UNREFERENCED_PARAMETER(gameObj);
	auto& sceneManager = ::SceneManager::GetInstance();
	sceneManager.PreviousScene();
}


