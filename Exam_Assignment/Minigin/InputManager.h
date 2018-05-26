#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>
#include <map>
#include "Command.h"

class GameObject;

enum class ControllerButton
{
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000
};

enum class GameController
{
	Controller1 = 0,
	Controller2 = 1,
	Controller3 = 2,
	Controller4 = 3,
	KeyBoard1 = 4,
	KeyBoard2 = 5,
	GlobalCommands = 6,
	ControllerLimit = 7
};

class InputManager final : public Singleton<InputManager>
{
public:
	bool ProcessInput();

	void BindControllerKey(GameController player, ControllerButton button, std::shared_ptr<Command> command);
	void BindKeyboardKey(GameController player, SDL_Scancode key, std::shared_ptr<Command> command);
	
	void SetPlayer(GameController id, std::weak_ptr<GameObject> gameObj) {mGameObjects[(int)id] = gameObj; }

	bool IsDown(SDL_Scancode key);
	bool IsReleased(SDL_Scancode key);
	bool IsPressed(SDL_Scancode key);
	
	//void SetPlayer1(std::weak_ptr<GameObject> gameObj) { mPlayer1GameObj = gameObj; }
	//void SetPlayer2(std::weak_ptr<GameObject> gameObj) { mPlayer2GameObj = gameObj; }

private:
	XINPUT_STATE currentState{};

	std::map<SDL_Scancode, std::pair<GameController,std::shared_ptr<Command>>> mKeyMapping;
	std::map<std::pair<ControllerButton,GameController>, std::shared_ptr<Command>> mControllerMapping;

	//std::weak_ptr<GameObject> mPlayer1GameObj;
	//std::weak_ptr<GameObject> mPlayer2GameObj;

	bool mPressed[SDL_NUM_SCANCODES] = { false };

	std::weak_ptr<GameObject> mGameObjects[int(GameController::ControllerLimit)];
};
