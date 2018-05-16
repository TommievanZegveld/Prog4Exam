#include "MiniginPCH.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "RenderComponent.h"


TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font) :
	mNeedsUpdate(true),
	mText(text),
	mFont(font)
{
}


TextComponent::~TextComponent()
{
}

void TextComponent::Update(float deltaTime)
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
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) {
			std::stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}
}

void TextComponent::Render()
{
	if (mRenderComp == nullptr)
	{
		mRenderComp = mGameObject->GetComponent<RenderComponent>();
		if (mRenderComp == nullptr)
		{
			mRenderComp = new RenderComponent(mTexture);
			mGameObject->AddComponent(mRenderComp);
		}
	}
	mRenderComp->Render();
}

void TextComponent::SetText(const std::string& text)
{
	mNeedsUpdate = true;
	mText = text;
}

void TextComponent::SetFont(std::shared_ptr<Font> font)
{
	mFont = font;
	mNeedsUpdate = true;
}
