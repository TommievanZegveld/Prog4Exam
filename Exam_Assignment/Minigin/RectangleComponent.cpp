#include "MiniginPCH.h"
#include "RectangleComponent.h"
#include <SDL.h>
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"


RectangleComponent::RectangleComponent(float width,float height, Color col) : mWidth(width),mHeight(height), mCol(col)
{
}


RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto pos = mGameObject.lock()->GetTransform()->GetPosition();

	SDL_Rect wall;
	wall.x = (int)pos.x - int(mWidth * 0.5f);
	wall.y = (int)pos.y - int(mHeight * 0.5f);
	wall.h = (int)mHeight;
	wall.w = (int)mWidth;

	auto& renderer = Renderer::GetInstance();

	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), mCol.r, mCol.g, mCol.b, 255);
	SDL_RenderFillRect(renderer.GetSDLRenderer(), &wall);
}
