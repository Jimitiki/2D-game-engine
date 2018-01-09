#include "Animation.hpp"
#include "SDLCore.hpp"

Animation::Animation(std::string *image_name, std::vector<SDL_Rect *> *src_rects, SDL_Rect *dest_rect, std::vector<int> *transition_times, int uniform_transition_time) 
		: Sprite(image_name, src_rects->at(0), dest_rect)
{
	this->src_rects = src_rects;
	this->transition_times = transition_times;
	this->uniform_transition_time = uniform_transition_time;
	if (transition_times == nullptr)
	{
		transition_timer = uniform_transition_time;
	}
	else
	{
		transition_timer = transition_times->at(0);
	}
}

Animation::~Animation()
{
	delete src_rects;
	if (transition_times != nullptr)
	{
		delete transition_times;
	}
}

void Animation::draw(SDL_Renderer *renderer)
{
	transition_timer -= Game::delta_time();
	if (transition_timer <= 0)
	{
		cur_rect_index++;
		if (cur_rect_index >= src_rects->size())
		{
			cur_rect_index = 0;
		}
		Src_rect(src_rects->at(cur_rect_index));
		if (transition_times == nullptr)
		{
			transition_timer = uniform_transition_time;
		}
		else
		{
			transition_timer = transition_times->at(cur_rect_index);
		}
	}
	Sprite::draw(renderer);
}