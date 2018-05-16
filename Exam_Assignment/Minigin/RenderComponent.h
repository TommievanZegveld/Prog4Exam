#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent(std::shared_ptr<Texture2D> texture);
	~RenderComponent();

	void Render() override;
	void Update(float dt) override;
private:
	std::shared_ptr<Texture2D> mTexture;
};