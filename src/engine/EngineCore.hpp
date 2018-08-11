#ifndef ENGINECORE_H_
#define ENGINECORE_H_

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#elif _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

#include <exception>

namespace Engine
{
	SDL_Renderer *get_renderer();
	int get_delta_time();
	int get_screen_height();
	int get_screen_width();
}

class at_capacity : public std::exception
{
	const char *what() const throw()
	{
		return "The capacity of this data structure has already been reached.";
	} 
};

void print_sdl_error();
void print_img_error();
void print_ttf_error();
void print_SDL_Rect(SDL_Rect *rect);

#endif