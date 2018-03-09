#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>

struct SDL_Renderer;
class FPSDisplay;

namespace Game {
	bool init(SDL_Renderer * renderer, int screen_height, int screen_width);
	void run();
};

#endif