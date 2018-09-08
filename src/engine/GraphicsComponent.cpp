#include "GraphicsComponent.hpp"

#include <string>

#include "AssetManager.hpp"

GraphicsComponent::GraphicsComponent(std::string* image_name, SDL_Rect* src, SDL_Rect* dest) : Component(Component::Type::GRAPHICS)
{
	Asset::image(image_name, &this->surface);
	this->src_rect = *src;
	this->dest_rect = *dest;
}