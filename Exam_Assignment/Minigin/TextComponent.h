#pragma once
#include "BaseComponent.h"
#include "types.h"

class TextureComponent;
class RenderComponent;
class Font;
class Texture2D;
class TextComponent : public BaseComponent
{
public:
	TextComponent(const std::string& text, std::shared_ptr<Font> font,Color col = Color{255,255,255});
	~TextComponent();

	void Update(float deltaTime) override;

	void SetText(const std::string& text);
	void SetFont(std::shared_ptr<Font> font);
	void SetColor(Color col);

private:
	bool mNeedsUpdate;
	std::string mText;
	std::shared_ptr< Font > mFont;
	std::shared_ptr < Texture2D > mTexture;
	Color mTextColor;
};