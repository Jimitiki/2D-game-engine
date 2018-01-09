#ifndef HUDELEMENT_HPP_
#define HUDELEMENT_HPP_

#include "geometry.hpp"

struct SDL_Rect;
struct SDL_Renderer;

class HUDElement
{
	public:
		HUDElement(PointF *position);
		virtual ~HUDElement();
		virtual void draw(SDL_Renderer *renderer) = 0;
		virtual void update(int delta_time) = 0;
	
	protected:
		SDL_Rect *Rect();
		void Rect(SDL_Rect *rect);

	private:
		SDL_Rect *rect = nullptr;
};

#endif