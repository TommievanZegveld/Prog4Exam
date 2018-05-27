#include "MiniginPCH.h"
#include "Fruit.h"
#include "Components.h"
#include <stdlib.h>
#pragma warning (disable:4244)
#include <random>
#include <chrono>
#include <thread>


Fruit::Fruit(glm::vec2 pos) : PickUp(pos)
{
}


Fruit::~Fruit()
{
}

void Fruit::Init()
{

	auto then1 = std::chrono::high_resolution_clock::now();

	GameObject::Init();

	auto rend = std::make_shared<RenderComponent>();
	AddComponent(rend);
	auto textureComp = std::make_shared<TextureComponent>();
	AddComponent(textureComp);

	std::this_thread::sleep_for(std::chrono::microseconds(20));
	auto now1 = std::chrono::high_resolution_clock::now();
	auto seed = std::chrono::duration_cast<std::chrono::microseconds>(now1 - then1);
	srand(seed.count());

	auto idx = rand() % mFruits.size();
	textureComp->SetTexture(mFruits[idx]);
	auto collider = std::make_shared<ColliderComponent>(mPosition, (float)rend->GetTextureSize().width, (float)rend->GetTextureSize().height, ColliderType::STATIC);
	AddComponent(collider);

	SetPosition(mPosition.x, mPosition.y);
	mScoreValue = 50;
}
