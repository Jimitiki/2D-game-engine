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
		void update(float delta_time);
		void draw();
		bool init();
		void quit();

		SDL_Renderer * renderer;
		SDL_Texture * fpsCounter = nullptr;
		SDL_Rect * fpsHolder;

		int screen_width;
		int screen_height;



		FPSDisplay *fps_display;


		int screen_r = 0x00;
		int screen_g = 0x00;
		int screen_b = 0x00;


    	int lastUpdateTime;
		int frameCounter = 0;
		int deltaT;
		int lastFPSCheck;

		const int FPS_UPDATE = 1000;
		const std::string FPS_FONT_NAME = "/home/chris/Documents/code/2D-game-engine/assets/font/FUTRFW.TTF";
		TTF_Font * fpsFont = nullptr;
};

#endif