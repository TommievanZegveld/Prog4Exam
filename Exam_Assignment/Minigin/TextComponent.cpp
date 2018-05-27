#include "MiniginPCH.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "RenderComponent.h"
#include "types.h"


TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, Color col) :
	mNeedsUpdate(true),
	mText(text),
	mFont(font),
	mTextColor(col)
	
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
		const SDL_Color color = { mTextColor.r,mTextColor.g,mTextColor.b };
		const auto surf = TTF_RenderText_Blended_Wrapped(mFont->GetFont(), mText.c_str(), color,480);
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

		auto mRenderComp = mGameObject.lock()->GetComponent<RenderComponent>();
		if (mRenderComp == nullptr)
		{
			std::cout << "Did you try updating a text component with a new text without first adding a rendercomponent?" << std::endl;
			return;
		}
		mRenderComp->SetTexture(mTexture);
	}
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

void TextComponent::SetColor(Color col)
{
	mNeedsUpdate = true;
	mTextColor = col;
}
