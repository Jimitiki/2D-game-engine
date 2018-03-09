#include "MenuElement.hpp"
#include "GameCore.hpp"
#include "Sprite.hpp"

MenuElement::MenuElement(SDL_Rect *rect, std::string *image_file)
		: MenuElement(rect, image_file, nullptr, nullptr, nullptr, nullptr) {}

MenuElement::MenuElement(SDL_Rect *rect, std::string *image_file, MenuElement *left,
		MenuElement *right, MenuElement *above, MenuElement *below)
{
	this->rect = new SDL_Rect;
	*(this->rect) = *rect;
	this->sprite = new Sprite(image_file, nullptr, rect);
	
	this->left = left;
	this->right = right;
	this->above = above;
	this->below = below;
}

MenuElement::~MenuElement()
{
	delete sprite;
	delete rect;
}

MenuElement *MenuElement::get_left()
{
	return left;
}

void MenuElement::set_left(MenuElement *menu_element)
{
	this->left = menu_element;
}

MenuElement *MenuElement::get_right()
{
	return right;
}

void MenuElement::set_right(MenuElement *menu_element)
{
	this->right = menu_element;
}

MenuElement *MenuElement::get_above()
{
	return above;
}

void MenuElement::set_above(MenuElement *menu_element)
{
	this->above = menu_element;
}

MenuElement *MenuElement::get_below()
{
	return below;
}

void MenuElement::set_below(MenuElement *menu_element)
{
	this->below = menu_element;
}

void MenuElement::set_on_select(std::function<void()>* on_select)
{
	this->on_select = *on_select;
}

void MenuElement::select()
{
	on_select();
}

void MenuElement::hover()
{

}

void MenuElement::update(int delta_time)
{

}

void MenuElement::draw(SDL_Renderer *renderer)
{
	sprite->draw(renderer);
}