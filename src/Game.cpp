#include "Game.hpp"
#include <cstring>
#include <sstream>

#include "SDLCore.hpp"
#include "geometry.hpp"
#include "FPSDisplay.hpp"
#include "AssetManager.hpp"
#include "HUDManager.hpp"
#include "Timer.hpp"

void display_fps(PointF *position, int refresh_ms)
{
	HUD::add(new FPSDisplay(position, refresh_ms));
}

namespace Game
{
	namespace
	{
		SDL_Renderer *game_renderer;
		int game_screen_width;
		int game_screen_height;

    	int prev_ticks;
		int delta_ticks;



		int screen_r = 0xFF;
		int screen_g = 0xFF;
		int screen_b = 0xFF;
	}

	void update_renderer(SDL_Renderer *renderer);
	void update_ticks(int ticks);
	void update();
	void draw();
	void quit();
}

SDL_Renderer *Game::renderer()
{
	return game_renderer;
}

int Game::delta_time()
{
	return delta_ticks;
}

bool Game::init(SDL_Renderer* renderer, int screen_height, int screen_width)
{
	game_renderer = renderer;
	game_screen_width = screen_width;
	game_screen_height = screen_height;
	PointF fps_position = {0.0f, 0.0f};
	display_fps(&fps_position, 600);
	fps_position.x = screen_width - 57.0f;
	fps_position.y = screen_height - 20.0f;
	display_fps(&fps_position, 1000);

    return true;
}

void Game::quit()
{
	HUD::destroy();
	Asset::unload_all();
}

void Game::run()
{
	bool end = false;
	prev_ticks = SDL_GetTicks();
	SDL_Event event;

	PointF fps_position = {57.0f, 20.0f};
	Timer::bind(std::bind(display_fps, &fps_position, 1380), 2000);

	while (!end)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				end = true;
			}
		}

		int ticks = SDL_GetTicks();
		delta_ticks = ticks - prev_ticks;

		const Uint8* key_states = SDL_GetKeyboardState(NULL);
		if (key_states[SDL_SCANCODE_ESCAPE] || (key_states[SDL_SCANCODE_LALT] || key_states[SDL_SCANCODE_RALT])
				&& key_states[SDL_SCANCODE_F4])
		{
			end = true;
		}
		if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
		{
			screen_b = 0xFF;
			screen_r = 0x00;
			screen_g = 0x00;
		}
		else if(key_states[SDL_SCANCODE_S] || key_states[SDL_SCANCODE_DOWN])
		{
			screen_b = 0x00;
			screen_r = 0xFF;
			screen_g = 0x00;
		}
		else if(key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
		{
			screen_b = 0xFF;
			screen_r = 0x00;
			screen_g = 0xFF;
		}
		else if (key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_UP])
		{
			screen_b = 0xFF;
			screen_r = 0xFF;
			screen_g = 0x00;
		}
		else
		{
			screen_b = 0xFF;
			screen_r = 0xFF;
			screen_g = 0xFF;
		}

		prev_ticks = ticks;

		update();
		draw();
	}
	quit();
}

void Game::update()
{
	HUD::update(delta_ticks);
	Timer::update(delta_ticks);
}

void Game::draw()
{
	SDL_SetRenderDrawColor(game_renderer, screen_r, screen_g, screen_b, 0xFF);
	SDL_RenderClear(game_renderer);

	HUD::draw(game_renderer);
	
	SDL_RenderPresent(game_renderer);
}