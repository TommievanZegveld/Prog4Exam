#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <SDL.h>

//#include "Texture2D.h" If included in header; everything is fine; but when forward declared and included in cpp it throws an "use of undefined type"Texture2D"
// Fix for now : include in header *DANGER*


RenderComponent::RenderComponent()
{
	auto test = 0;
	if (test == 0)
		test = 1;
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::Render()
{
	if (mTexture != nullptr)
	{
		const auto pos = mGameObject->GetTransform()->GetPosition();

		Renderer::GetInstance().RenderTexture(*mTexture, pos.x - (GetTextureSize().width * 0.5f), pos.y - (GetTextureSize().height * 0.5f));
	}
	else
	{
		std::cout << "RenderComponent::mTexture == nullptr" << std::endl;
	}
}

void RenderComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	mTexture = texture;
}

TextureSize RenderComponent::GetTextureSize()
{
	int w, h;
	SDL_QueryTexture(mTexture->GetSDLTexture(), NULL, NULL, &w, &h);
	return { w,h };
}
