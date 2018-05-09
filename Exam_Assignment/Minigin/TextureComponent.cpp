#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <SDL.h>
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"


TextureComponent::~TextureComponent()
{
}

void TextureComponent::Render()
{
	if (mTexture != nullptr)
	{
		auto pos = mGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}

void TextureComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TextureComponent::SetTexture(const std::string& fileName)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(fileName);

}
