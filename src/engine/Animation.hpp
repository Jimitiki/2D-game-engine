#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <vector>
#include "Sprite.hpp"

struct SDL_Rect;
struct SDL_Renderer;

struct Frame
{
	SDL_Rect *src_rect;
	int duration;
};

class Animation : public Sprite
{
	public:
		Animation(std::string *image_name, std::vector<Frame *> *frames, SDL_Rect *dest_rect);
		~Animation();
		virtual void draw(SDL_Renderer *renderer);

	private:
		std::vector<Frame *> *frames;
		SDL_Rect *dest_rect;

		unsigned int cur_frame = 0;
		int transition_timer;
};

#endif
