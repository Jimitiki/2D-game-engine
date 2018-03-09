#include "Game.hpp"
#include <cstring>
#include <sstream>

#include "GameCore.hpp"
#include "FPSDisplay.hpp"
#include "AssetManager.hpp"
#include "HUDManager.hpp"
#include "Timer.hpp"
#include "Cursor.hpp"
#include "rectd.hpp"
#include "InputManager.hpp"

void display_fps(point_d *position, int refresh_ms)
{
	HUD::add(new FPSDisplay(position, refresh_ms));
}

namespace Game
{
	SDL_Renderer *renderer;
	int screen_width;
	int screen_height;

	int prev_ticks;
	int delta_time;

	Cursor *cursor;
	bool draw_cursor;
	bool end;

	int screen_r = 0xFF;
	int screen_g = 0xFF;
	int screen_b = 0xFF;

	Input::callback sr;
	Input::callback esc;

	void update();
	void draw();
	void quit();

	void escape(SDL_Event *event);
	void screen_red(SDL_Event *event);
}


void Game::screen_red(SDL_Event *event)
{
	screen_r = 0xFF;
	screen_g = 0x00;
	screen_b = 0x00;
}

void Game::escape(SDL_Event *event)
{
	end = true;
}

SDL_Renderer *Game::get_renderer()
{
	return Game::renderer;
}

int Game::get_delta_time()
{
	return delta_time;
}

bool Game::init(SDL_Renderer* renderer, int screen_height, int screen_width)
{
	Game::renderer = renderer;
	Game::screen_width = screen_width;
	Game::screen_height = screen_height;
	point_d fps_position = {0.0f, 0.0f};
	display_fps(&fps_position, 600);
	fps_position.x = screen_width - 57.0f;
	fps_position.y = screen_height - 20.0f;
	display_fps(&fps_position, 1000);

	sr = screen_red;
	Input::bind_key_hold(SDL_SCANCODE_W, &sr);

	esc = escape;
	Input::bind_key_down(SDL_SCANCODE_ESCAPE, &esc);

    return true;
}

void Game::quit()
{
	HUD::destroy();
	Asset::unload_all();
}

void Game::run()
{
	end = false;
	prev_ticks = SDL_GetTicks();
	SDL_Event event;

	point_d fps_position = {57.0f, 20.0f};
	Timer::bind(std::bind(display_fps, &fps_position, 1380), 2000);

	point_d cursor_size = {14.0f, 20.0f};
	std::string cursor_image = "cursor.png";
	cursor = new Cursor(&cursor_image, nullptr, &cursor_size);
	enable_cursor();

	while (!end)
	{
		screen_b = 0xFF;
		screen_r = 0xFF;
		screen_g = 0xFF;

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				end = true;
			}
			else
			{
				Input::handle_input_event(&event);
			}
		}

		int ticks = SDL_GetTicks();
		delta_time = ticks - prev_ticks;

		// const Uint8* key_states = SDL_GetKeyboardState(NULL);
		// if (key_states[SDL_SCANCODE_ESCAPE] 
		// 		|| ((key_states[SDL_SCANCODE_LALT] 
		// 		|| key_states[SDL_SCANCODE_RALT])
		// 		&& key_states[SDL_SCANCODE_F4]))
		// {
		// 	end = true;
		// }
		// if (key_states[SDL_SCANCODE_A] || key_states[SDL_SCANCODE_LEFT])
		// {
		// 	screen_b = 0xFF;
		// 	screen_r = 0x00;
		// 	screen_g = 0x00;
		// }
		// else if(key_states[SDL_SCANCODE_S] || key_states[SDL_SCANCODE_DOWN])
		// {
		// 	screen_b = 0x00;
		// 	screen_r = 0xFF;
		// 	screen_g = 0x00;
		// }
		// else if(key_states[SDL_SCANCODE_D] || key_states[SDL_SCANCODE_RIGHT])
		// {
		// 	screen_b = 0xFF;
		// 	screen_r = 0x00;
		// 	screen_g = 0xFF;
		// }
		// else if (key_states[SDL_SCANCODE_W] || key_states[SDL_SCANCODE_UP])
		// {
		// 	screen_b = 0xFF;
		// 	screen_r = 0xFF;
		// 	screen_g = 0x00;
		// }

		prev_ticks = ticks;

		update();
		draw();
	}
	quit();
}

void Game::update()
{
	Input::update();
	HUD::update(delta_time);
	Timer::update(delta_time);

	if (draw_cursor && cursor != nullptr)
	{
		cursor->update(delta_time);
	}
}

void Game::draw()
{
	SDL_SetRenderDrawColor(renderer, screen_r, screen_g, screen_b, 0xFF);
	SDL_RenderClear(renderer);

	HUD::draw(renderer);
	if (draw_cursor && cursor != nullptr)
	{
		cursor->draw(renderer);
	}
	
	SDL_RenderPresent(renderer);
}

void Game::set_cursor(Cursor *cursor)
{
	Game::cursor = cursor;
}

void Game::disable_cursor()
{
	draw_cursor = false;
}

void Game::enable_cursor()
{
	draw_cursor = true;
}

bool Game::is_cursor_enabled()
{
	return draw_cursor;
}