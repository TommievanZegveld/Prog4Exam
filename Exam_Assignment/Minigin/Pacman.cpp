#include "MiniginPCH.h"
#include "Pacman.h"
#include "Components.h"


Pacman::Pacman()
{

}


Pacman::~Pacman()
{
}

void Pacman::Init()
{
	//	Attaching Transform from original GameObject
	GameObject::Init();

	auto rend = std::make_shared<RenderComponent>();
	AddComponent(rend);
	auto textComp = std::make_shared<TextureComponent>();
	AddComponent(textComp);
	textComp->SetTexture("pacman.png");
	auto colComp = std::make_shared<ColliderComponent>(GetTransform()->GetPosition(), (float)rend->GetTextureSize().width, (float)rend->GetTextureSize().height, ColliderType::DYNAMIC);
	AddComponent(colComp);
}

void Pacman::Update(float deltaTime)
{
	//	Update all the components first
	for (size_t i = 0; i < mComponents.size(); ++i)
	{
		mComponents[i]->Update(deltaTime);
	}

	UNREFERENCED_PARAMETER(deltaTime);
	auto test = 5;
	std::cout << test << std::endl;
}
