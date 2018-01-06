#include "Game.hpp"
#include <cstring>
#include <sstream>

#include "geometry.hpp"
#include "FPSDisplay.hpp"

Uint32 pauseCallback(Uint32 interval, void* param);

Game::Game(SDL_Renderer* renderer, int screen_height, int screen_width) 
{
	this->renderer = renderer;
	this->screen_width = screen_width;
	this->screen_height = screen_height;
}

Game::~Game()
{
	delete fps_display;
}

bool Game::init()
{
	point_f fps_position = {0.0f, 0.0f};
	fps_display = new FPSDisplay(&fps_position, 600);

    return true;
}

void Game::quit()
{

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
	lastUpdateTime = SDL_GetTicks();
	SDL_Event event;
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		int currentTime = SDL_GetTicks();
		deltaT = currentTime - lastUpdateTime;


		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_ESCAPE] || (currentKeyStates[SDL_SCANCODE_LALT] || currentKeyStates[SDL_SCANCODE_RALT])
				&& currentKeyStates[SDL_SCANCODE_F4])
		{
			quit = true;
		}
		if (currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_LEFT])
		{
			screen_b = 0xFF;
			screen_r = 0x00;
			screen_g = 0x00;
		}
		else if(currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_DOWN])
		{
			screen_b = 0x00;
			screen_r = 0xFF;
			screen_g = 0x00;
		}
		else if(currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			screen_b = 0xFF;
			screen_r = 0x00;
			screen_g = 0xFF;
		}
		else if (currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_UP])
		{
			screen_b = 0xFF;
			screen_r = 0xFF;
			screen_g = 0x00;
		}
		else
		{
			screen_b = 0x00;
			screen_r = 0x00;
			screen_g = 0x00;
		}

		lastUpdateTime = currentTime;

		update(deltaT);
		draw();
	}
}

void Game::update(int delta_time)
{
	fps_display->update(delta_time);
}

void Game::draw()
{
	SDL_SetRenderDrawColor(renderer, screen_r, screen_g, screen_b, 0xFF);
	SDL_RenderClear(renderer);

	fps_display->draw(renderer);

	SDL_RenderPresent(renderer);
}