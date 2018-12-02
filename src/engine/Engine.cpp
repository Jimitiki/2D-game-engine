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
#include "EventManager.hpp"
#include "InputManager.hpp"

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
	void terminate(SDL_Event* event, void* arg);

	void escape(void* arg);
}

void Engine::escape(void* arg)
{
	SDL_QuitEvent* quit_event = new SDL_QuitEvent;
	quit_event->type = SDL_QUIT;
	//quit_event->timestamp = key_event->timestamp;
	SDL_PushEvent((SDL_Event*) quit_event);
}

void Engine::terminate(SDL_Event* event, void* arg)
{
	Engine::end = true;
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
	Engine::end = false;
	prev_ticks = SDL_GetTicks();
	SDL_Event event;

	Stage::start_scene(scene);

	Event::Handler quit_handler{SDL_QUIT, Engine::terminate, nullptr};
	Event::bind(&quit_handler);
	Input::Handler esc_handler{SDLK_ESCAPE, Engine::escape, nullptr};
	Input::bind(&esc_handler);

	while (!Engine::end)
	{
		while (SDL_PollEvent(&event));

		int ticks = SDL_GetTicks();
		delta_time = ticks - prev_ticks;

		prev_ticks = ticks;

		update();
		draw();
	}
	Event::unbind(&quit_handler);
	Input::unbind(&esc_handler);
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
