#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include "SDLCore.hpp"

class FPSDisplay;

class Game {
	public:
		Game(SDL_Renderer * renderer, int screen_height, int screen_width);
		~Game();
		void start();

	private:
		void run();
		void update(int delta_time);
		void draw();
		bool init();
		void quit();

		SDL_Renderer * renderer;

		int screen_width;
		int screen_height;



		FPSDisplay *fps_display;


		int screen_r = 0x00;
		int screen_g = 0x00;
		int screen_b = 0x00;


    	int lastUpdateTime;
		int deltaT;
};

#endif