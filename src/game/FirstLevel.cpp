#include "FirstLevel.hpp"

#include <functional>

#include "../engine/HUDManager.hpp"
#include "../engine/Timer.hpp"
#include "FPSDisplay.hpp"

void display_fps(PointD *position, int refresh_ms);

FPSDisplay *fps_display;

void add_fps(SDL_Event *event);
void delete_fps(SDL_Event *event);
Input::CallbackID fps_callback_id;

std::vector<Entity *> * FirstLevel::init()
{
	PointD *fps_position = new PointD;
	fps_position->x = 0.0f;
	fps_position->y = 0.0f;
	display_fps(fps_position, 600);
	fps_position->x = Engine::get_screen_width() - 57.0f;
	fps_position->y = Engine::get_screen_height() - 20.0f;
	display_fps(fps_position, 1000);

	fps_position->x = 57.0f;
	fps_position->y = 20.0f;
	Timer::Callback fn = std::bind(display_fps, fps_position, 1380);
	Timer::bind(&fn, 2000);


	Input::Callback fps = add_fps;
	fps_callback_id = Input::bind_key_down(SDL_SCANCODE_W, &fps);
	
	entities = new std::vector<Entity *>();
	return entities;
}

void display_fps(PointD *position, int refresh_ms)
{
	HUD::add(new FPSDisplay(position, refresh_ms));
}

void add_fps(SDL_Event *event)
{
	if (fps_display != nullptr)
	{
		return;
	}
	PointD fps_position = {Engine::get_screen_width() / 2.0f,  Engine::get_screen_height() / 2.0f};
	fps_display = new FPSDisplay(&fps_position, 970);
	HUD::add(fps_display);

	Input::unbind(fps_callback_id);
}

void delete_fps(SDL_Event *event)
{
	delete fps_display;
	fps_display = nullptr;
}