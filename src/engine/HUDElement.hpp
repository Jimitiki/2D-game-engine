#ifndef HUDELEMENT_HPP_
#define HUDELEMENT_HPP_

#include "EngineCore.hpp"
#include "RectD.hpp"

class HUDElement
{
	public:
		HUDElement(PointD *position);
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