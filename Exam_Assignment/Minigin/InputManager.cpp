#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"

bool InputManager::ProcessInput()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		dwResult = XInputGetState(i, &currentState);
		//	Using an iterator we obtain the current controller

		if (dwResult == ERROR_SUCCESS)
		{
			//	Controller is connected

			//	The Game Objects in our mGameObjects and our GameController enum are mapped 1:1
			//	So we check wether that game object exists; for example; we might map the buttons to a controller
			//	But we might not attach a gameobject to this controller yet; this check makes sure we don't call functions on nullptr
			if (!mGameObjects[i].lock())
				continue;

			//	We iterate through a hex value that is equal to the hex value given in Xinput.h
			//	We set our own ControllerButton values to these hex values so we can add/remove buttons and continue using our own defined ControllerButton
			for (int j = 0x0001; j <= 0x8000; j*=2)
			{
				if (currentState.Gamepad.wButtons & j)
				{
					//	We get the command pointer by accessing it through our map; our map exists of map < pair<Button,Controler>,Command>
					//	We map the button along the controller so that every controller has it's own button ( which is desired)
					//		I first had it map only a button to a pair of <controller,command> such as with Keyboard input; but this would mean only
					//		4 buttons could be mapped, shared across the controllers
					//	If our command exists; aka we mapped a command to our button/controller combo
					//	We execute it.
					auto var = mControllerMapping[std::make_pair(ControllerButton(j), GameController(i))];
					if(var)
						//	Because we mapped our Controller and GameObjects on a 1:1 basis we can execute using the [i] index
						var->execute(mGameObjects[i]);
				}
			}
		}
		else
		{
			//Controller is not connected
		}
	}

	//	If I Don't poll the events the window gets stuck and no input can be read;
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	//	GetKeyBoardState returns an array of integers; 0 for released; 1 for down;
	//	SDL_NUM_SCANCODES is defined in SDL_scancode.h
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		//	If a button is down
		if(state[i])
		{
			//	var is a pair of <GameController,Command>
			auto var = mKeyMapping[SDL_Scancode(i)];
			//	var.first contains a GameController; by casting it to an int we can check wether a gameObject exists
			//	var.second contains a Command and we need to make sure this Command exists;
			//	So first w check wether gameobject exists and then check if there's a command linked to the mapped key;
			if(mGameObjects[int(var.first)].lock() && var.second && IsPressed(SDL_Scancode(i)))
			{
				//	Execute the command on the gameObject associated with the GameController
				var.second->execute(mGameObjects[int(var.first)]);
			}
		}
	}

	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		if (!state[i] && mPressed[i])
			mPressed[i] = false;
	}


	return true;
}

void InputManager::BindControllerKey(GameController player, ControllerButton button, std::shared_ptr<Command> command)
{
	if (!mControllerMapping.insert(std::make_pair(std::make_pair(button,player),command)).second)
		mControllerMapping[std::make_pair(button,player)] =  command;
}

void InputManager::BindKeyboardKey(GameController player, SDL_Scancode key, std::shared_ptr<Command> command)
{
	//	Map.insert() returns an std::pair <iterator,bool> the bool returns a true if insert is completed; and false if failed (aka, key already exists)
	//	In that case change the command
	if (!mKeyMapping.insert(std::make_pair(key, std::make_pair(player, command))).second)
		mKeyMapping[key] = std::make_pair(player, command);
}

bool InputManager::IsDown(SDL_Scancode key)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[key])
		return true;

	return false;
}

bool InputManager::IsReleased(SDL_Scancode key)
{


	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (mPressed[key])
		if (!state[key])
		{
			mPressed[key] = false;
			return true;
		}
	return false;
}

bool InputManager::IsPressed(SDL_Scancode key)
{
	if(!IsReleased(key)) // Resetting to released for every pressed function call if necessary
		if(!mPressed[key])
			if (IsDown(key))
			{
				mPressed[key] = true;
				return true;
			}
	return false;
}


