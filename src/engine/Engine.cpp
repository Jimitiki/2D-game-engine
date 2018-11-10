#include "Engine.hpp"
#include <cstring>
#include <sstream>

#include "EngineCore.hpp"
#include "AssetManager.hpp"
#include "GraphicsManager.hpp"
#include "InputManager.hpp"
#include "HUDManager.hpp"
#include "Timer.hpp"
#include "Cursor.hpp"
#include "geometry.hpp"
#include "Stage.hpp"


namespace Engine
{
	SDL_Renderer *renderer;
	int screen_width;
	int screen_height;

	int prev_ticks;
	int delta_time;

	bool end;

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

	Graphics::init(renderer);
	Input::init();

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

	Stage::start_scene(scene);

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
		delta_time = ticks - prev_ticks;

		prev_ticks = ticks;

		update();
		draw();
	}
	quit();
}

void Engine::update()
{
	HUD::update(delta_time);
	Timer::update(delta_time);
	Stage::update(delta_time);
	Cursor::update(delta_time);
}

void Engine::draw()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	HUD::draw(renderer);
	Stage::draw(renderer);
	Cursor::draw(renderer);
	
	SDL_RenderPresent(renderer);
}
