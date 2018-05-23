#include "MiniginPCH.h"
#include "Pacman.h"
#include "Components.h"


Pacman::Pacman()
{
	auto rend = std::make_shared<RenderComponent>();
	AddComponent(rend);
	auto textComp = std::make_shared<TextureComponent>();
	AddComponent(textComp);
	textComp->SetTexture("pacman.png");
	auto colComp = std::make_shared<ColliderComponent>(GetTransform()->GetPosition(), (float)rend->GetTextureSize().width, (float)rend->GetTextureSize().height, ColliderType::DYNAMIC);
	AddComponent(colComp);
}


Pacman::~Pacman()
{
}
