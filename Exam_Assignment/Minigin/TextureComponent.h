#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae
{
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = default;
		~TextureComponent();

		void Render() override;
		void Update(float deltaTime) override;

		void SetTexture(const std::string& fileName);



		TextureComponent(const TextureComponent &) = delete;
		TextureComponent(TextureComponent &&) = delete;
		TextureComponent & operator= (const TextureComponent &) = delete;
		TextureComponent & operator= (const TextureComponent &&) = delete;
	private:
		std::shared_ptr<Texture2D> mTexture;
	};
}

