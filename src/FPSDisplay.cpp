#include <sstream>
#include <vector>

#include "FPSDisplay.hpp"
#include "GameCore.hpp"
#include "AssetManager.hpp"
#include "Animation.hpp"

FPSDisplay::FPSDisplay(PointF *position, int update_time) : HUDElement(position)
{
	this->update_time = update_time;
	Asset::font(&FONT_NAME, FONT_SIZE, &font);
	std::vector<SDL_Rect *> *rects = new std::vector<SDL_Rect *>();
	for (int i = 0; i < 7; i++)
	{
		SDL_Rect *src_rect = new SDL_Rect;
		src_rect->h = 20;
		src_rect->w = 56;
		if (i < 4)
		{
			src_rect->x = i * 57;
		}
		else
		{
			src_rect->x = (6 - i) * 57;
		}
		src_rect->y = 0;
		rects->push_back(src_rect);
	}
	SDL_Rect *sprite_rect = new SDL_Rect;
	sprite_rect->h = 20;
	sprite_rect->w = 56;
	sprite_rect->x = position->x;
	sprite_rect->y = position->y;
	std::string sprite_image = "fpsbackground_anim.png";
	background = new Animation(&sprite_image, rects, sprite_rect, nullptr, 200);
	//background = new Sprite(&sprite_image, rects->at(2), sprite_rect);
}

void FPSDisplay::update(int delta_time)
{
	frame_counter++;
	elapsed_time += delta_time;
	if (elapsed_time >= update_time)
	{
		fps = frame_counter / (elapsed_time / 1000.0f);
		elapsed_time = 0;
		frame_counter = 0;
	}
}

void FPSDisplay::draw(SDL_Renderer *renderer)
{
	if (fps < 0)
	{
		return;
	}
	background->draw(renderer);
	if (elapsed_time == 0)
	{
		SDL_DestroyTexture(texture);
		
		std::stringstream fps_stream;
		fps_stream << fps;
		std::string fps_string = fps_stream.str();

		SDL_Surface *fps_surface = TTF_RenderText_Solid(font, fps_string.c_str(), {0, 0, 0});
		if (fps_surface == nullptr)
		{
			print_ttf_error();
			return;
		}
		get_rect()->w = fps_surface->w;
		get_rect()->h = fps_surface->h; 
		texture = SDL_CreateTextureFromSurface(renderer, fps_surface);

		SDL_FreeSurface(fps_surface);
	}
	SDL_RenderCopy(renderer, texture, nullptr, get_rect());
}