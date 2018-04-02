#include "EngineCore.hpp"
#include "Engine.hpp"
#include <string>
#include <iostream>
#include <sstream>

bool init(SDL_Window **window, SDL_Renderer **renderer, int *screen_width, int *screen_height);
void close(SDL_Window **window, SDL_Renderer **renderer);
void print_sdl_error();
void print_img_error();
void print_ttf_error();

int main(int argc, char *args[])
{
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	int screen_width = 0;
	int screen_height = 0;

	if (init(&window, &renderer, &screen_height, &screen_width))
	{
		SDL_ShowCursor(SDL_DISABLE);
		if (Engine::init(renderer, screen_height, screen_width))
		{
			Engine::run();
		}
	}
	close(&window, &renderer);

	return 0;
}

bool init(SDL_Window **window, SDL_Renderer **renderer, int *screen_height, int *screen_width)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		print_sdl_error();
		return false;
	}
	
	int image_flags = IMG_INIT_PNG;
	if (!(IMG_Init(image_flags) & image_flags))
	{
		print_img_error();
		return false;
	}

	if (TTF_Init() == -1)
	{
		print_ttf_error();
		return false;
	}
	
	SDL_DisplayMode display_mode;

	//Handles multiple displays
	/*for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
	{
		if (SDL_GetCurrentDisplayMode(i, &display_mode) != 0)
		{
			continue;
		}

		screen_width += display_mode.w;
		if (screen_height < display_mode.h)
		{
			screen_height = display_mode.h;
		}
	}*/

	//Just one
	if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0)
	{
		print_sdl_error();
		return false;
	}

	*screen_width = display_mode.w;
	*screen_height = display_mode.h;

	*window = SDL_CreateWindow("I AM SO TIRED", 0, 0, *screen_width, *screen_height, SDL_WINDOW_BORDERLESS);
	if (*window == NULL)
	{
		print_sdl_error();
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
		return false;
	}
	SDL_SetRenderDrawColor(*renderer, 0x00, 0x00, 0x00, 0x00);

	return true;
}

void close(SDL_Window **window, SDL_Renderer **renderer)
{
	SDL_DestroyWindow(*window);
	SDL_DestroyRenderer(*renderer);
	TTF_Quit();
	SDL_Quit();
}
