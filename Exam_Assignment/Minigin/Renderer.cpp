#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "RenderComponent.h"

#include <chrono>

void Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	if (mRenderer == nullptr) {
		std::stringstream ss; ss << "SDL_CreateRenderer Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
}

void Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	for (size_t i = 0; i < m_RenderComponents.size(); i++)
	{
		m_RenderComponents[i]->Render();
	}

	auto then3 = std::chrono::high_resolution_clock::now();
	SDL_RenderPresent(mRenderer);
	auto now3 = std::chrono::high_resolution_clock::now();
	auto test3 = std::chrono::duration<float>(now3 - then3);

	//std::cout << "Render Call from Renderer: " << test3.count() << std::endl;
	
}

void Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}

	//for (size_t i = 0; i < m_RenderComponents.size(); i++)
	//{
	//	m_RenderComponents[i] = nullptr;
	//}
	//m_RenderComponents.clear();
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}
