#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <string>

struct SDL_Renderer;
class FPSDisplay;

namespace Engine {
	bool init(SDL_Renderer * renderer, int screen_height, int screen_width);
	void run();
};

#endif