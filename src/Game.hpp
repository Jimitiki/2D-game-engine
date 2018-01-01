#ifndef GAME_H_
#define GAME_H_

#include "SDLCore.hpp"

class Game {
	public:
		Game(SDL_Renderer * renderer, int screen_height, int screen_width);
		~Game();
		void start();

	private:
		void run();
		void update();
		void draw();
		bool init();
		void quit();

		SDL_Renderer * renderer;

		int screen_width;
		int screen_height;



		int screen_r = 0x00;
		int screen_g = 0x00;
		int screen_b = 0x00;
};

#endif