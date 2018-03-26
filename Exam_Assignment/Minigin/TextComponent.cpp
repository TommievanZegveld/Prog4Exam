#include "MiniginPCH.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"


dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<dae::Font> font) :
	mNeedsUpdate(true),
	mText(text),
	mFont(font)
{
}


dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (mNeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr) {
			std::stringstream ss; ss << "Render text failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) {
			std::stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<dae::Texture2D>(texture);
	}
}

void dae::TextComponent::Render()
{
	if (mTexture != nullptr)
	{
		const auto pos = mGameObject->GetTransform()->GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	mNeedsUpdate = true;
	mText = text;
}

void dae::TextComponent::SetFont(std::shared_ptr<dae::Font> font)
{
	mFont = font;
	mNeedsUpdate = true;
}
