#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <SDL.h>
#include "Renderer.h"
#include "ResourceManager.h"


dae::TextureComponent::~TextureComponent()
{
}

void dae::TextureComponent::Render()
{
	if (mTexture != nullptr)
	{
		auto pos = mGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}

void dae::TextureComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::TextureComponent::SetTexture(const std::string& fileName)
{
	mTexture = dae::ResourceManager::GetInstance().LoadTexture(fileName);

}
