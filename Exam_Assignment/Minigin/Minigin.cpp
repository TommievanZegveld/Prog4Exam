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

const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps

void Initialize();
void LoadGame();
void Cleanup();

std::shared_ptr<GameObject> mFPSCounter = std::make_shared<GameObject>();
std::string mFPSString = "";

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		while(doContinue) 
		{
			auto current = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(current - t).count();

			int fps = int(1 / deltaTime);
			mFPSString = ("fps= " + std::to_string(fps));
			mFPSCounter->GetComponent<TextComponent>()->SetText(mFPSString);

			mFPSCounter->GetTransform()->Move(0.5f, 0.0f, 0.0f);

			doContinue = input.ProcessInput();

			sceneManager.Update(deltaTime);
			renderer.Render();

			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<GameObject>();
	auto texture = new TextureComponent();
	texture->SetTexture("background.jpg");
	go->AddComponent(texture);
	scene.Add(go);

	auto go2 = std::make_shared<GameObject>();
	auto texture2 = new TextureComponent();
	texture2->SetTexture("logo.png");
	go2->AddComponent(texture2);
	go2->SetPosition(216, 180);
	scene.Add(go2);
	
	auto go3 = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = new TextComponent("Programming 4 Assignment",font);
	go3->AddComponent(text);
	go3->SetPosition(80, 20);
	scene.Add(go3);

	auto startText = new TextComponent("fps: ", font);
	mFPSCounter->AddComponent(startText);
	mFPSCounter->SetPosition(10, 10);
	scene.Add(mFPSCounter);
}

void Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

