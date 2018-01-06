#ifndef HUDELEMENT_HPP_
#define HUDELEMENT_HPP_

#include "IGameElement.hpp"
#include "geometry.hpp"

struct SDL_Rect;
class SDL_Renderer;

class HUDElement : public IGameElement
{
	public:
		HUDElement(point_f *position);
		~HUDElement();
		virtual void draw(SDL_Renderer *renderer) = 0;
		virtual void update(int delta_time) = 0;
		SDL_Rect *Rect();
		void Rect(SDL_Rect *rect);
	protected:
		SDL_Rect *rect = nullptr;
};

#endif