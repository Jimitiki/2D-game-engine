#include "GraphicsManager.hpp"

#include "GraphicsComponent.hpp"

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
			std::vector<Component*>* components = entity->get_components_by_type(Component::Type::GRAPHICS);
			for (int i = 0; i < components->size(); i++)
			{
				GraphicsComponent* component = (GraphicsComponent*) (components->at(i));
				if (component->texture == nullptr)
				{
					component->texture = SDL_CreateTextureFromSurface(Engine::get_renderer(), component->surface);
				}
				SDL_Rect dest = *component->dest_rect;
				SDL_RenderCopy(renderer, component->texture, component->src_rect, &dest);
			}
		}
	}
}