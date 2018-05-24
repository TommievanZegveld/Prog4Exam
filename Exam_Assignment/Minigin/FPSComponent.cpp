#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <chrono>



FPSComponent::FPSComponent() : 
	TextComponent("fps: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), Color{0,255,0})
{	
}


FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update(float dt)
{	
	int fps = int(1 / dt);
	std::string fpsString("fps: " + std::to_string(fps));
	SetText(fpsString);

	TextComponent::Update(dt);
}
