#include "HUDElement.hpp"
#include "SDLCore.hpp"

HUDElement::HUDElement(PointF *position)
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