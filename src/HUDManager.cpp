#include <vector>
#include "HUDManager.hpp"
#include "GameCore.hpp"

namespace HUD
{
	namespace
	{
		std::vector<HUDElement *> hud_elements;
	}
}

void HUD::add(HUDElement *element)
{
	hud_elements.push_back(element);
}

void HUD::update(int delta_time)
{
	for (unsigned int i = 0; i < hud_elements.size(); i++)
	{
		hud_elements[i]->update(delta_time);
	}
}

void HUD::draw(SDL_Renderer *renderer)
{
	for (unsigned int i = 0; i < hud_elements.size(); i++)
	{
		hud_elements[i]->draw(renderer);
	}
}

void HUD::destroy()
{
	for (unsigned int i = 0; i < hud_elements.size(); i++)
	{
		delete hud_elements[i];
	}
}