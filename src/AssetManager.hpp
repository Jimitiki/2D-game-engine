#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <string>

#include "SDLCore.hpp"

namespace Asset
{
	bool font(std::string *font_name, int font_size, TTF_Font **font);
	bool surface(std::string *image_name, SDL_Surface **surface);
	void destroy();
}

#endif