#include "Engine.hpp"
#include <cstring>
#include <sstream>

#include "EngineCore.hpp"
#include "AssetManager.hpp"
#include "HUDManager.hpp"
#include "Timer.hpp"
#include "Cursor.hpp"
#include "RectD.hpp"
#include "InputManager.hpp"
#include "Stage.hpp"


namespace Engine
{
	SDL_Renderer *renderer;
	int screen_width;
	int screen_height;

	int prev_ticks;
	int delta_time;

	Cursor *cursor;
	bool draw_cursor;
	bool end;

	Input::Callback esc;

	void update();
	void draw();
	void quit();

	void escape(SDL_Event *event);
}

void Engine::escape(SDL_Event *event)
{
	end = true;
}

SDL_Renderer *Engine::get_renderer()
{
	return Engine::renderer;
}

int Engine::get_delta_time()
{
	return delta_time;
}

int Engine::get_screen_height()
{
	return screen_height;
}

int Engine::get_screen_width()
{
	return screen_width;
}

bool Engine::init(SDL_Renderer* renderer, int screen_height, int screen_width)
{
	Engine::renderer = renderer;
	Engine::screen_width = screen_width;
	Engine::screen_height = screen_height;

	esc = escape;
	Input::bind_key_down(SDL_SCANCODE_ESCAPE, &esc);

    return true;
}

void Engine::quit()
{
	HUD::destroy();
	Asset::unload_all();
}

void Engine::run(IScene *scene)
{
	end = false;
	prev_ticks = SDL_GetTicks();
	SDL_Event event;

	Stage::play_scene(scene);
	PointD cursor_size = {14.0f, 20.0f};
	std::string cursor_image = "cursor.png";
	cursor = new Cursor(&cursor_image, nullptr, &cursor_size);
	enable_cursor();

	while (!end)
	{
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

		prev_ticks = ticks;

		update();
		draw();
	}
	quit();
}

void Engine::update()
{
	Input::update();
	HUD::update(delta_time);
	Timer::update(delta_time);
	Stage::update(delta_time);

	if (draw_cursor && cursor != nullptr)
	{
		cursor->update(delta_time);
	}
}

void Engine::draw()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	HUD::draw(renderer);
	Stage::draw(renderer);
	if (draw_cursor && cursor != nullptr)
	{
		cursor->draw(renderer);
	}
	
	SDL_RenderPresent(renderer);
}

void Engine::set_cursor(Cursor *cursor)
{
	Engine::cursor = cursor;
}

void Engine::disable_cursor()
{
	draw_cursor = false;
}

void Engine::enable_cursor()
{
	draw_cursor = true;
}

bool Engine::is_cursor_enabled()
{
	return draw_cursor;
}