#include "MiniginPCH.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#pragma comment(lib,"xinput.lib")
#include "SDL.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
#include "Log.h"

#include "GameCommands.h"
#include "PacManScene.h"
#include "ColliderManager.h"

#include <fstream>
#include "SelectionScene.h"

//const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps

void Initialize();
void LoadGame();
void Cleanup();

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	auto GlobalInputObject = std::make_shared<GameObject>();
	
	{
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		//	Adding Next/Prev scene buttons
		auto nextCommand = std::make_shared<NextCommand>();
		auto prevCommand = std::make_shared<PreviousCommand>();

		input.BindKeyboardKey(GameController::GlobalCommands, SDL_SCANCODE_LEFTBRACKET, prevCommand);
		input.BindKeyboardKey(GameController::GlobalCommands, SDL_SCANCODE_RIGHTBRACKET, nextCommand);
		// Creating a dummy object to create and control global commands;
		input.SetPlayer(GameController::GlobalCommands, GlobalInputObject);

		auto then = std::chrono::high_resolution_clock::now();

		bool doContinue = true;
		while(doContinue) 
		{
			auto now = std::chrono::high_resolution_clock::now();

			auto deltaTime = std::chrono::duration<float>(now - then);

				auto then1 = std::chrono::high_resolution_clock::now();
			doContinue = input.ProcessInput();
				auto now1 = std::chrono::high_resolution_clock::now();
				auto test1 = std::chrono::duration<float>(now1 - then1);

				auto then2 = std::chrono::high_resolution_clock::now();
			sceneManager.Update(deltaTime.count());
				auto now2 = std::chrono::high_resolution_clock::now();
				auto test2 = std::chrono::duration<float>(now2 - then2);

				auto then3 = std::chrono::high_resolution_clock::now();
			sceneManager.Render();
				auto now3 = std::chrono::high_resolution_clock::now();
				auto test3 = std::chrono::duration<float>(now3 - then3);


			/*std::cout << "ProcessInput: " << test1.count()
						<< "  UpdateMethod: " << test2.count() 
					<< 	"  RenderCall: " << test3.count() 
				<< "  DeltaTime: " << deltaTime.count() << std::endl;*/


			then = now;
		}
	}

	Cleanup();
    return 0;
}

SDL_Window* window;

void Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,                    
		480,                    
		SDL_WINDOW_OPENGL       
	);
	if (window == nullptr) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	Renderer::GetInstance().Init(window);
}

void LoadGame()
{
	SceneManager::GetInstance().AddScene(std::make_shared<SelectionScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<PacManScene>());
}

void Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

