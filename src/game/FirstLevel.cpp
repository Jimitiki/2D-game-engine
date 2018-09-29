#include "FirstLevel.hpp"

#include <functional>

#include "../engine/HUDManager.hpp"
#include "../engine/Timer.hpp"
#include "../engine/Cursor.hpp"
#include "../engine/InputComponent.hpp"
#include "../engine/GraphicsComponent.hpp"
#include "../engine/TransformComponent.hpp"
#include "SquareMovementComponent.hpp"
#include "UserControlComponent.hpp"
#include "SquareControlComponent.hpp"
#include "FPSDisplay.hpp"



void display_fps(Vec2D *position, int refresh_ms);

FPSDisplay *fps_display;

void add_fps(SDL_Event *event);
void delete_fps(SDL_Event *event);

std::vector<Entity *> * FirstLevel::init()
{
	Vec2D *fps_position = new Vec2D;
	fps_position->x = 0.0f;
	fps_position->y = 0.0f;
	display_fps(fps_position, 600);

	Vec2D cursor_size = {14.0f, 20.0f};
	std::string cursor_image = "cursor.png";
	Cursor::init_cursor(&cursor_image, nullptr, &cursor_size);
	Cursor::enable_cursor();
	
	entities = new std::vector<Entity *>();
	SDL_Rect src = {0, 0, 1, 1};
	SDL_Rect dest = {0, 0, 60, 60};
	std::string square_img = "black_dot.png";
	for (int i = 0; i < 5; i++)
	{
		Entity* entity = new Entity();

		Vec2D position = {300 + i * 200, 200 + i * 100};
		Vec2D scale = {1, 1};

		entity->add_component(new GraphicsComponent(&square_img, &src, &dest));
		entity->add_component(new TransformComponent(&position, 0, &scale));
		entity->add_component(new SquareMovementComponent(200 + i * 100, 1 - i * 0.1));
		entities->push_back(entity);
	}

	Entity* entity = new Entity();
	Vec2D position = {1200, 900};
	Vec2D scale = {1, 1};
	Vec2D velocity = {0, 0};
	SquareControlComponent *component = new SquareControlComponent();

	entity->add_component(component);
	entity->add_component(new GraphicsComponent(&square_img, &src, &dest));
	entity->add_component(new TransformComponent(&position, 0, &scale));
	entity->add_component(new MovementComponent(&velocity, 0));
	entities->push_back(entity);

	entity = new Entity();
	position = {0, 0};
	UserControlComponent* u_component = new UserControlComponent();
	InputComponent* i_component = new InputComponent();
	i_component->key_inputs[SDL_SCANCODE_LEFT] = "movel";
	i_component->key_inputs[SDL_SCANCODE_RIGHT] = "mover";
	i_component->key_inputs[SDL_SCANCODE_UP] = "moveu";
	i_component->key_inputs[SDL_SCANCODE_DOWN] = "moved";

	entity->add_component(u_component);
	entity->add_component(i_component);
	entity->add_component(new GraphicsComponent(&square_img, &src, &dest));
	entity->add_component(new TransformComponent(&position, 0, &scale));
	entity->add_component(new MovementComponent(&velocity, 0));
	entities->push_back(entity);

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
}

void delete_fps(SDL_Event *event)
{
	delete fps_display;
	fps_display = nullptr;
}