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
	virtual void draw(SDL_Renderer *renderer);

protected:
	void set_src_rect(SDL_Rect *src_rect);
	void set_dest_rect(SDL_Rect *dest_rect);

private:
	SDL_Texture *texture = nullptr;
	SDL_Rect *src_rect = nullptr;
	SDL_Rect *dest_rect = nullptr;
};

#endif