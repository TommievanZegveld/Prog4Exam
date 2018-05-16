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

void TextureComponent::Render()
{
	if (mRenderComp == nullptr)
	{
		mRenderComp = mGameObject->GetComponent<RenderComponent>();
		if (mRenderComp == nullptr)
		{
			mRenderComp = new RenderComponent(mTexture);
			mGameObject->AddComponent(mRenderComp);
		}
	}
	mRenderComp->Render();
}

void TextureComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TextureComponent::SetTexture(const std::string& fileName)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}
