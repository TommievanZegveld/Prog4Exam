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
	auto mRenderComp = mGameObject->GetComponent<RenderComponent>();
	if (mRenderComp == nullptr)
	{
		std::cout << "Did you try setting a texture on a texture component without first adding a render component?" << std::endl;
		return;
	}
	mTexture = ResourceManager::GetInstance().LoadTexture(fileName);
	mRenderComp->SetTexture(mTexture);
}
