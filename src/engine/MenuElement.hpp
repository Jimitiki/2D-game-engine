#ifndef MENUELEMENT_HPP_
#define MENUELEMENT_HPP_

#include <string>
#include <functional>

struct SDL_Rect;
struct SDL_Renderer;
class Sprite;

class MenuElement
{
	public:
		MenuElement(SDL_Rect *rect, std::string *image_file);
		MenuElement(SDL_Rect *rect, std::string *image_file, MenuElement *left, MenuElement *right, MenuElement *above, MenuElement *below);
		~MenuElement();

		MenuElement *get_left();
		void set_left(MenuElement *menu_element);
		MenuElement *get_right();
		void set_right(MenuElement *menu_element);
		MenuElement *get_above();
		void set_above(MenuElement *menu_element);
		MenuElement *get_below();
		void set_below(MenuElement *menu_element);

		void set_on_select(std::function <void ()> *on_select);

		void hover();
		void select();
		void update(int delta_time);
		void draw(SDL_Renderer *renderer);

	private:
		MenuElement *left;
		MenuElement *right;
		MenuElement *above;
		MenuElement *below;

		Sprite *sprite;
		SDL_Rect *rect;

		std::function <void ()> on_select;
};

#endif