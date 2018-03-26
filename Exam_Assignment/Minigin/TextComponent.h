#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	class TextureComponent;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<dae::Font> font);
		~TextComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<dae::Font> font);

	private:
		bool mNeedsUpdate;
		std::string mText;
		std::shared_ptr< dae::Font > mFont;
		std::shared_ptr < dae::Texture2D > mTexture;
	};
}
