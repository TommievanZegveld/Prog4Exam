#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <chrono>



FPSComponent::FPSComponent() : 
	TextComponent("fps: ", ResourceManager::GetInstance().LoadFont("Lingua.otf", 36))
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

	//mGameObject->SetPosition(mGameObject->GetTransform()->GetPosition().x + 1, mGameObject->GetTransform()->GetPosition().y + 1);

	TextComponent::Update(dt);
}

void FPSComponent::Render()
{
	TextComponent::Render();
}
