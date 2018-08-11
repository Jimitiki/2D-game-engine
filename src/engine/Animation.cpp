#include "Animation.hpp"
#include "EngineCore.hpp"

Animation::Animation(std::string *image_name, std::vector<Frame *> *frames, SDL_Rect *dest_rect)
		: Sprite(image_name, frames->at(0)->src_rect, dest_rect)
{
	this->frames = frames;
	transition_timer = frames->at(0)->duration;
}

Animation::~Animation()
{
	for (auto frame : *frames)
	{
		delete frame;
	}
	delete frames;
}

void Animation::draw(SDL_Renderer *renderer)
{
	transition_timer -= Engine::get_delta_time();
	if (transition_timer <= 0)
	{
		if (++cur_frame >= frames->size())
		{
			cur_frame = 0;
		}
		set_src_rect(frames->at(cur_frame)->src_rect);
		transition_timer = frames->at(cur_frame)->duration;
	}
	Sprite::draw(renderer);
}