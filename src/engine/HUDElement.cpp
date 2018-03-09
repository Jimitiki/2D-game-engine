#include "HUDElement.hpp"
#include "GameCore.hpp"

HUDElement::HUDElement(point_d *position)
{
	rect = new SDL_Rect;
	rect->x = position->x;
	rect->y = position->y;
}

HUDElement::~HUDElement()
{
	//delete rect;
}

SDL_Rect *HUDElement::get_rect()
{
	return rect;
}

void HUDElement::set_rect(SDL_Rect *rect)
{
	this->rect = rect;
}