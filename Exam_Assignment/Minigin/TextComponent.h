#pragma once
#include "BaseComponent.h"

class TextureComponent;
class RenderComponent;
class Font;
class Texture2D;
class TextComponent : public BaseComponent
{
public:
	TextComponent(const std::string& text, std::shared_ptr<Font> font);
	~TextComponent();

	void Update(float deltaTime) override;
	void Render() override;

	void SetText(const std::string& text);
	void SetFont(std::shared_ptr<Font> font);

private:
	bool mNeedsUpdate;
	std::string mText;
	std::shared_ptr< Font > mFont;
	std::shared_ptr < Texture2D > mTexture;

	RenderComponent* mRenderComp;
};