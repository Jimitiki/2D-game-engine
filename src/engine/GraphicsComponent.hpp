#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include "EngineCore.hpp"
#include "Sprite.hpp"
#include "rectd.hpp"

class GraphicsComponent
{
    public:
        GraphicsComponent(point_d *position);
        void update(double delta_time);
        void draw(SDL_Renderer *renderer);

    private:
        point_d *position;
        Sprite *sprite;
};

#endif