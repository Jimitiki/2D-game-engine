#ifndef HUDMANAGER_HPP_
#define HUDMANAGER_HPP_

#include "HUDElement.hpp"

struct SDL_Renderer;

namespace HUD
{
	void add(HUDElement *hud_element);
	void update(int delta_time);
	void draw(SDL_Renderer *renderer);
	void destroy();
}

#endif