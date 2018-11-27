#include "Stage.hpp"
#include "Entity.hpp"
#include "ControlManager.hpp"
#include "GraphicsManager.hpp"
#include "MovementManager.hpp"
#include "TransformManager.hpp"
#include "InputManager.hpp"

namespace Stage
{
	Vec2D bounds;
	std::vector<Entity *> *entities;
}

Vec2D Stage::get_bounds()
{
	return bounds;
}

void Stage::play_scene(IScene *scene)
{
	entities = scene->init();
}

void Stage::update(int delta_time)
{
	Movement::update(delta_time, Stage::entities);
	Transform::update(delta_time, Stage::entities);
	Control::update(delta_time, Stage::entities);
}

void Stage::draw(SDL_Renderer *renderer)
{
	Graphics::draw(Stage::entities);
}