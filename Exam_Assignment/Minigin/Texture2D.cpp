#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return mTexture;
}

Texture2D::Texture2D(SDL_Texture* texture)
{
	mTexture = texture;
}
