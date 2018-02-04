#ifndef HUDELEMENT_HPP_
#define HUDELEMENT_HPP_

#include "rectd.hpp"

struct SDL_Rect;
struct SDL_Renderer;

class HUDElement
{
	public:
		HUDElement(point_d *position);
		virtual ~HUDElement();
		virtual void draw(SDL_Renderer *renderer) = 0;
		virtual void update(int delta_time) = 0;
	
	protected:
		SDL_Rect *get_rect();
		void set_rect(SDL_Rect *rect);

	private:
		SDL_Rect *rect = nullptr;
};

#endif