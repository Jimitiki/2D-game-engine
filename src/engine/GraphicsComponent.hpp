#ifndef GRAPHICSCOMPONENT_HPP
#define GRAPHICSCOMPONENT_HPP

#include "EngineCore.hpp"
#include "Sprite.hpp"
#include "RectD.hpp"

class GraphicsComponent
{
    public:
        GraphicsComponent(PointD *position);
        void update(double delta_time);
        void draw(SDL_Renderer *renderer);

    private:
        PointD *position;
        Sprite *sprite;
};

#endif