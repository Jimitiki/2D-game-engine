#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

class Sprite
{
	public:
		Sprite(std::string *image_name, SDL_Rect *src_rect, SDL_Rect *dest_rect);
		virtual ~Sprite();
		virtual void update(int delta_time);
		virtual void draw(SDL_Renderer *renderer);

	protected:
		void Src_rect(SDL_Rect *src_rect);

	private:
		SDL_Texture *texture;
		std::string image_name;
		SDL_Rect *src_rect;
		SDL_Rect *dest_rect;
};

#endif