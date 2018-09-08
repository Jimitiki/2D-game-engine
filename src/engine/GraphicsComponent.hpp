#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include "Component.hpp"
#include "EngineCore.hpp"
#include "Sprite.hpp"
#include "geometry.hpp"

class GraphicsComponent : public Component
{
    public:
        GraphicsComponent(std::string* image_name, int src_x, int src_y, int src_h, int src_w, int dest_x, int dest_y, int dest_h, int dest_w);
		virtual ~GraphicsComponent();
		virtual void update(int delta_time) {}

		SDL_Surface* surface;
		SDL_Rect* src_rect;
		SDL_Rect* dest_rect;
		SDL_Texture* texture;
		uint32_t layer;
};

#endif