#include "HUDElement.hpp"
#include "SDLCore.hpp"

HUDElement::HUDElement(point_f *position)
{
	rect = new SDL_Rect;
	rect->x = position->x;
	rect->y = position->y;
}

HUDElement::~HUDElement()
{
	//delete rect;
}

SDL_Rect *HUDElement::Rect()
{
	return rect;
}

void HUDElement::Rect(SDL_Rect *rect)
{
	this->rect = rect;
}