#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <string>

#include "EngineCore.hpp"

namespace Asset
{
	bool font(std::string *font_name, int font_size, TTF_Font **font);
	bool image(std::string *image_name, SDL_Surface **surface);
	void unload_all();
}

#endif