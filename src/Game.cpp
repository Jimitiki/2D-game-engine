#include "Game.hpp"
#include <cstring>

Uint32 pauseCallback(Uint32 interval, void* param);

Game::Game(SDL_Renderer* renderer, int screen_height, int screen_width) 
{
	this->renderer = renderer;
	this->screen_width = screen_width;
	this->screen_height = screen_height;
}

Game::~Game()
{
}

bool Game::init()
{
    return true;
}

void Game::quit()
{
	SDL_DestroyRenderer(renderer);
}

void Game::start()
{
	if (init())
	{
		run();
	}
	quit();
}

void Game::run()
{
	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
			{
				printf("AAAA\n");
			}
		}


		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates)

		update();
		draw();
	}
}

void Game::update()
{

}

void Game::draw()
{
	SDL_SetRenderDrawColor(renderer, screen_r, screen_g, screen_b, 0xFF);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}