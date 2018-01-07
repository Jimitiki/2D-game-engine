#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>

struct SDL_Renderer;
class FPSDisplay;

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

    	int prev_ticks;
		int delta_time;



		int screen_r = 0xFF;
		int screen_g = 0xFF;
		int screen_b = 0xFF;
};

#endif