#ifndef GAME_H_
#define GAME_H_

#include "SDLCore.hpp"

class Game {
	public:
		Game(SDL_Renderer * renderer, int screenHeight, int screenWidth);
		~Game();
		void start();

	private:
		void run();
		void update();
		void draw();
		bool init();
		void quit();

		SDL_Renderer * renderer;

		int screenWidth;
		int screenHeight;



		int screen_r = 0;
		int screen_g = 0;
		int screen_b = 0;
};

#endif