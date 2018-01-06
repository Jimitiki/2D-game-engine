#ifndef IGAMEELEMENT_HPP_
#define IGAMEELEMENT_HPP_

class SDL_Renderer;

class IGameElement
{
	public:
		virtual void update(int delta_time) = 0;
		virtual void draw(SDL_Renderer *renderer) = 0;
};

#endif