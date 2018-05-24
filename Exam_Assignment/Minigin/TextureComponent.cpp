#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <SDL.h>
#include "Renderer.h"
#include "ResourceManager.h"
#include "RenderComponent.h"

//#include "Texture2D.h" If included in header; everything is fine; but when forward declared and included in cpp it throws an "use of undefined type"Texture2D"
// Fix for now : include in header *DANGER*


TextureComponent::~TextureComponent()
{
}

void TextureComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TextureComponent::SetTexture(const std::string& fileName)
{
	if(!mGameObject.lock())
		throw std::runtime_error("You tried setting a texture in TextureComponent without first adding it to the GameObject");

	auto mRenderComp = mGameObject.lock()->GetComponent<RenderComponent>();
	if (!mRenderComp)
	{
		throw std::runtime_error("Did you try setting a texture on a texture component without first adding a render component?");
	}
	mTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	mRenderComp->SetTexture(mTexture);
}
