#ifndef FPSDISPLAY_HPP_
#define FPSDISPLAY_HPP_

#include "SDLCore.hpp"
#include "HUDElement.hpp"
#include "geometry.hpp"


class FPSDisplay : private HUDElement
{
	public:
		FPSDisplay(int update_time);
		FPSDisplay(point_f *position, int update_time);
		void update(float delta_time);
		void draw(SDL_Renderer *renderer);

	private:
		SDL_Texture *texture;
		TTF_Font *font;

		int update_time = 2000;
		float elapsed_time = 0;
		int frame_counter = 0;
		int fps = -1;
};

#endif