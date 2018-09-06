#include "GraphicsComponent.hpp"

#include <string>

#include "AssetManager.hpp"

GraphicsComponent::GraphicsComponent(std::string* image_name, int src_x, int src_y, int src_h, int src_w, int dest_x, int dest_y, int dest_h, int dest_w) : Component(Component::Type::GRAPHICS)
{
	Asset::image(image_name, &this->surface);
	this->src_rect = new SDL_Rect;
	this->src_rect->x = src_x;
	this->src_rect->y = src_y;
	this->src_rect->h = src_h;
	this->src_rect->w = src_w;
	this->dest_rect = new SDL_Rect;
	this->dest_rect->x = dest_x;
	this->dest_rect->y = dest_y;
	this->dest_rect->h = dest_h;
	this->dest_rect->w = dest_w;
}

GraphicsComponent::~GraphicsComponent()
{
	delete this->src_rect;
	delete this->dest_rect;
}