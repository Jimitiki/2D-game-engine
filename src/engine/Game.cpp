#include "Game.hpp"

#include <iostream>

#include "EngineCore.hpp"
#include "Engine.hpp"

Game::Game()
{
	renderer = nullptr;
	window = nullptr;
	screen_height = 0;
	screen_width = 0;
}

bool Game::init_window()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) < 0)
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

	screen_width = display_mode.w;
	screen_height = display_mode.h;

	window = SDL_CreateWindow("I AM SO TIRED", 0, 0, screen_width, screen_height, SDL_WINDOW_BORDERLESS);
	if (window == nullptr)
	{
		print_sdl_error();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

	return true;
}

bool Game::start_game(IScene *scene)
{
	SDL_GameController *controller = NULL;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		controller = SDL_GameControllerOpen(i);
		if (controller) {
			std::cout << "Found a valid controller, named: " << SDL_GameControllerName(controller) << "\n";
		}
	}

	if (Engine::init(renderer, screen_height, screen_width))
	{
		Engine::run(scene);
	}
	else
	{
		return false;
	}
	return true;
}

void Game::close_window()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
