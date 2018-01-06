#ifndef HUDELEMENT_HPP_
#define HUDELEMENT_HPP_

#include "IGameElement.hpp"
#include "geometry.hpp"

class SDL_Rect;
class SDL_Renderer;

class HUDElement : public IGameElement
{
	public:
		HUDElement();
		HUDElement(point_f *position);
		virtual void draw(SDL_Renderer *renderer) = 0;
		virtual void update(float delta_time) = 0;
		SDL_Rect *Rect();
		void Rect(SDL_Rect *rect);
	private:
		SDL_Rect *rect;
};

#endif