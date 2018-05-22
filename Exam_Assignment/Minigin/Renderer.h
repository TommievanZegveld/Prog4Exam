#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

class RenderComponent;

class Texture2D;
class Renderer final : public Singleton<Renderer>
{
	SDL_Renderer* mRenderer = nullptr;

public:
	void Init(SDL_Window* window);
	void Render();
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

	SDL_Renderer* GetSDLRenderer() const { return mRenderer; }

	void AddRenderComponent(std::shared_ptr<RenderComponent> comp) { m_RenderComponents.push_back(comp); }
private:
	std::vector <std::shared_ptr<RenderComponent>> m_RenderComponents;
};

