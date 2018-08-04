#ifndef GAME_HPP_
#define GAME_HPP_

#include "EngineCore.hpp"

class Game
{
public:
	Game();
	bool init_window();
	bool start_game();
	void close_window();

private:
	SDL_Renderer *renderer;
	SDL_Window *window;
	unsigned int screen_height;
	unsigned int screen_width;
};

#endif