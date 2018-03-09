#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <vector>
#include "Sprite.hpp"

struct SDL_Rect;
struct SDL_Renderer;

class Animation : public Sprite
{
	public:
		Animation(std::string *image_name, std::vector<SDL_Rect *> *src_rects, SDL_Rect *dest_rect, std::vector<int> *transition_times, int uniform_transition_time);
		~Animation();
		virtual void draw(SDL_Renderer *renderer);

	private:
		std::vector<SDL_Rect *> *src_rects;
		std::vector<int> *transition_times = nullptr;
		int uniform_transition_time;

		int cur_rect_index = 0;
		int transition_timer;
};

#endif
