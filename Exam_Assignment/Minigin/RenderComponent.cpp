#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"

//#include "Texture2D.h" If included in header; everything is fine; but when forward declared and included in cpp it throws an "use of undefined type"Texture2D"
// Fix for now : include in header *DANGER*


RenderComponent::RenderComponent(std::shared_ptr<Texture2D> texture) : mTexture(texture)
{
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::Render()
{
	if (mTexture != nullptr)
	{
		const auto pos = mGameObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}

void RenderComponent::Update(float dt)
{
	UNREFERENCED_PARAMETER(dt);
}
