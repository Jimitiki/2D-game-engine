#include "Stage.hpp"
#include "Entity.hpp"
#include "GraphicsManager.hpp"

namespace Stage
{
	namespace
	{
		
	}
	PointD bounds;
	std::vector<Entity *> *entities;
}

PointD Stage::get_bounds()
{
	return bounds;
}

void Stage::play_scene(IScene *scene)
{
	entities = scene->init();
}

void Stage::update(int delta_time)
{

}

void Stage::draw(SDL_Renderer *renderer)
{
	Graphics::draw(Stage::entities);
}