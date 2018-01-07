#include "Game.hpp"
#include <cstring>
#include <sstream>

#include "SDLCore.hpp"
#include "geometry.hpp"
#include "FPSDisplay.hpp"
#include "AssetManager.hpp"
#include "HUDManager.hpp"

namespace GameUtil
{
	namespace
	{
		SDL_Renderer *game_renderer;
		int delta_ticks;
	}

	void update_renderer(SDL_Renderer *renderer);
	void update_ticks(int ticks);
}

SDL_Renderer *GameUtil::renderer()
{
	return game_renderer;
}

void GameUtil::update_renderer(SDL_Renderer *renderer)
{
	game_renderer = renderer;
}

int GameUtil::delta_time()
{
	return delta_ticks;
}

void GameUtil::update_ticks(int ticks)
{
	delta_ticks = ticks;
}

Game::Game(SDL_Renderer* renderer, int screen_height, int screen_width) 
{
	this->renderer = renderer;
	GameUtil::update_renderer(renderer);
	this->screen_width = screen_width;
	this->screen_height = screen_height;
}

Game::~Game()
{
}

bool Game::init()
{
	point_f fps_position = {0.0f, 0.0f};
	HUD::add(new FPSDisplay(&fps_position, 600));
	// fps_position.x = screen_width - 57.0f;
	// fps_position.y = screen_height - 20.0f;
	// HUD::add(new FPSDisplay(&fps_position, 600));

    return true;
}

void Game::quit()
{
	Asset::unload_all();
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
	prev_ticks = SDL_GetTicks();
	SDL_Event event;
	bool fps_spawned = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		int ticks = SDL_GetTicks();
		delta_time = ticks - prev_ticks;
		GameUtil::update_ticks(delta_time);

		const Uint8* key_states = SDL_GetKeyboardState(NULL);
		if (key_states[SDL_SCANCODE_ESCAPE] || (key_states[SDL_SCANCODE_LALT] || key_states[SDL_SCANCODE_RALT])
				&& key_states[SDL_SCANCODE_F4])
		{
			quit = true;
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
			screen_b = 0x00;
			screen_r = 0x00;
			screen_g = 0x00;
		}

		prev_ticks = ticks;

		// if (ticks >= 580 && !fps_spawned)
		// {
		// 	fps_spawned = true;
		// 	point_f fps_position = {57.0f, 20.0f};
		// 	HUD::add(new FPSDisplay(&fps_position, 600));
		// }

		update();
		draw();
	}
}

void Game::update()
{
	HUD::update(GameUtil::delta_time());
}

void Game::draw()
{
	SDL_SetRenderDrawColor(renderer, screen_r, screen_g, screen_b, 0xFF);
	SDL_RenderClear(renderer);

	HUD::draw(renderer);

	SDL_RenderPresent(renderer);
}