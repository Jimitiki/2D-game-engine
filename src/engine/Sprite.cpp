#include <exception>

#include "Sprite.hpp"
#include "EngineCore.hpp"
#include "AssetManager.hpp"

Sprite::Sprite(std::string *image_name, SDL_Rect *src_rect, SDL_Rect *dest_rect)
{
	this->src_rect = new SDL_Rect;
	this->dest_rect = new SDL_Rect;
	if (src_rect != nullptr)
	{
		*(this->src_rect) = *src_rect;
	}
	if (dest_rect != nullptr)
	{
		*(this->dest_rect) = *dest_rect;
	}
	SDL_Surface *surface;
	Asset::image(image_name, &surface);

	texture = SDL_CreateTextureFromSurface(Engine::get_renderer(), surface);
	if (texture == nullptr)
	{
		print_sdl_error();
	}
}

Sprite::~Sprite()
{
	if (src_rect != nullptr)
	{
		delete src_rect;
	}
	if (dest_rect != nullptr)
	{
		delete dest_rect;
	}
	SDL_DestroyTexture(texture);
}

void Sprite::draw(SDL_Renderer *renderer)
{
	SDL_Rect dest = *dest_rect;
	if (texture != nullptr)
	{
		SDL_RenderCopy(renderer, texture, src_rect, &dest);
	}
}

void Sprite::Src_rect(SDL_Rect *src_rect)
{
	this->src_rect = src_rect;
}