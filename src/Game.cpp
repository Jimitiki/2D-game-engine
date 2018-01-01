#include "Game.hpp"
#include <string.h>

Uint32 pauseCallback(Uint32 interval, void* param);

Game::Game(SDL_Renderer* renderer, int screenHeight, int screenWidth) 
{
	this->renderer = renderer;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
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
		}

		update();
		draw();
	}
}

void Game::update()
{

}

void Game::draw()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}