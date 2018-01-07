#include <cstdio>
#include "SDLCore.hpp"

void print_sdl_error()
{
	printf("SDL error: %s\n", SDL_GetError());
}

void print_img_error()
{
	printf("IMAGERROR: %s\n", IMG_GetError());
}


void print_ttf_error()
{
	printf("E  R  R  O  R  : %s\n", TTF_GetError());
}

void printSDLRect(SDL_Rect *rect)
{
	printf("SDL_Rect (%p): \tx: %d, y: %d, w: %d, h: %d\n", rect, rect->x, rect->y, rect->w, rect->h);
}