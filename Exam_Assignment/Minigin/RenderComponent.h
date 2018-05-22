#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	void Render();
	void Update(float dt) override;

	void SetTexture(std::shared_ptr<Texture2D> texture);
private:
	std::shared_ptr<Texture2D> mTexture;
};