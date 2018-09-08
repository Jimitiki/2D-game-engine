#include "GraphicsManager.hpp"

#include "GraphicsComponent.hpp"
#include "TransformComponent.hpp"

namespace Graphics
{
	SDL_Renderer* renderer;
}

void Graphics::init(SDL_Renderer* renderer)
{
	Graphics::renderer = renderer;
}

void Graphics::draw(const std::vector<Entity*>* entities)
{
	for (Entity* entity : *entities)
	{
		if (entity->get_type_id() & Component::Type::GRAPHICS)
		{
			GraphicsComponent* component = (GraphicsComponent*) entity->get_component(Component::Type::GRAPHICS);
			if (entity->get_type_id() & Component::Type::TRANSFORM)
			{
				TransformComponent* t_component = (TransformComponent*) entity->get_component(Component::Type::TRANSFORM);
				component->dest_rect.x = t_component->position.x;
				component->dest_rect.y = t_component->position.y;
			}
			if (component->texture == nullptr)
			{
				component->texture = SDL_CreateTextureFromSurface(Engine::get_renderer(), component->surface);
			}
			SDL_Rect dest = component->dest_rect;
			SDL_RenderCopy(renderer, component->texture, &component->src_rect, &dest);
		}
	}
}