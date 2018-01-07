#ifndef SDLCORE_H_
#define SDLCORE_H_

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#elif _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#endif

namespace GameUtil
{
	SDL_Renderer *renderer();
	int delta_time();
}

void print_sdl_error();
void print_img_error();
void print_ttf_error();

#endif