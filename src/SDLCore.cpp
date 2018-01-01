#include <cstdio>
#include "SDLCore.hpp"

void printSDLError()
{
	printf("SDL error: %s\n", SDL_GetError());
}

void printIMGError()
{
	printf("IMAGERROR: %s\n", IMG_GetError());
}


void printTTFError()
{
	printf("E  R  R  O  R  : %s\n", TTF_GetError());
}