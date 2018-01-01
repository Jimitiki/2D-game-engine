#include "SDLCore.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>
#include <sstream>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int screenWidth = 0;
int screenHeight = 0;

Game* game;

bool init();
void close();
void printSDLError();
void printIMGError();
void printTTFError();

int main(int argc, char* args[])
{
	if (init())
	{
		game = new Game(renderer, screenHeight, screenWidth);
		game->start();
	}
	close();

	return 0;
}
bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		printSDLError();
		return false;
	}
	SDL_DisplayMode displayMode;

	//Handles multiple displays
	/*for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
	{
		if (SDL_GetCurrentDisplayMode(i, &displayMode) != 0)
		{
			continue;
		}

		screenWidth += displayMode.w;
		if (screenHeight < displayMode.h)
		{
			screenHeight = displayMode.h;
		}
	}*/

	//Just one
	if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
	{
		printSDLError();
		return false;
	}

	screenWidth = displayMode.w;
	screenHeight = displayMode.h;

	window = SDL_CreateWindow("I AM SO TIRED", 0, 0, screenWidth, screenHeight, SDL_WINDOW_BORDERLESS);
	if (window == NULL)
	{
		printSDLError();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printIMGError();
		return false;
	}

	if (TTF_Init() == -1)
	{
		printTTFError();
		return false;
	}

	return true;
}

void close()
{
	delete game;

	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
