#ifndef FPSDISPLAY_HPP_
#define FPSDISPLAY_HPP_

#include <string>

#include "SDLCore.hpp"
#include "HUDElement.hpp"
#include "geometry.hpp"

class Sprite;

class FPSDisplay : public HUDElement
{
	public:
		FPSDisplay(PointF *position, int update_time);
		void update(int delta_time);
		void draw(SDL_Renderer *renderer);

	private:
		SDL_Texture *texture = nullptr;
		TTF_Font *font = nullptr;

		Sprite *background;

		std::string FONT_NAME = "Futrfw.ttf";
		int FONT_SIZE = 14;

		int update_time;
		int elapsed_time = 0;
		int frame_counter = 0;
		int fps = -1;
};

#endif