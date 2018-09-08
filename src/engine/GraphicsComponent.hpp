#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include "Component.hpp"
#include "EngineCore.hpp"
#include "Sprite.hpp"
#include "geometry.hpp"

class GraphicsComponent : public Component
{
    public:
        GraphicsComponent(std::string* image_name, SDL_Rect* src, SDL_Rect* dest);
		virtual void update(int delta_time) {}

		SDL_Surface* surface;
		SDL_Rect src_rect;
		SDL_Rect dest_rect;
		SDL_Texture* texture;
		uint32_t layer;
};

#endif