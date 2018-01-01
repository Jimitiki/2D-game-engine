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

void printSDLError();
void printIMGError();
void printTTFError();

#endif