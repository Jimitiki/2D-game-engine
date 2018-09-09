#include "FirstLevel.hpp"

#include <functional>

#include "../engine/HUDManager.hpp"
#include "../engine/Timer.hpp"
#include "../engine/Cursor.hpp"
#include "../engine/GraphicsComponent.hpp"
#include "../engine/TransformComponent.hpp"
#include "SquareMovementComponent.hpp"
#include "FPSDisplay.hpp"

void display_fps(Vec2D *position, int refresh_ms);

FPSDisplay *fps_display;

void add_fps(SDL_Event *event);
void delete_fps(SDL_Event *event);
Input::CallbackID fps_callback_id;

std::vector<Entity *> * FirstLevel::init()
{
	Vec2D *fps_position = new Vec2D;
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


	//Input::Callback fps = add_fps;
	//fps_callback_id = Input::bind_key_down(SDL_SCANCODE_W, &fps);

	Vec2D cursor_size = {14.0f, 20.0f};
	std::string cursor_image = "cursor.png";
	Cursor::init_cursor(&cursor_image, nullptr, &cursor_size);
	Cursor::enable_cursor();
	
	entities = new std::vector<Entity *>();
	for (int i = 0; i < 5; i++)
	{
		Entity* entity = new Entity();

		SDL_Rect src = {0, 0, 1, 1};
		SDL_Rect dest = {200, 200, 60, 60};

		Vec2D position = {300 + i * 200, 200 + i * 100};
		Vec2D scale = {1, 1};

		entity->add_component(new GraphicsComponent(&std::string("black_dot.png"), &src, &dest));
		entity->add_component(new TransformComponent(&position, 0, &scale));
		entity->add_component(new SquareMovementComponent(200 + i * 100, 1 - i * 0.1));
		entities->push_back(entity);
	}
	return entities;
}

void display_fps(Vec2D *position, int refresh_ms)
{
	HUD::add(new FPSDisplay(position, refresh_ms));
}

void add_fps(SDL_Event *event)
{
	if (fps_display != nullptr)
	{
		return;
	}
	Vec2D fps_position = {Engine::get_screen_width() / 2.0f,  Engine::get_screen_height() / 2.0f};
	fps_display = new FPSDisplay(&fps_position, 970);
	HUD::add(fps_display);

	Input::unbind(fps_callback_id);
}

void delete_fps(SDL_Event *event)
{
	delete fps_display;
	fps_display = nullptr;
}