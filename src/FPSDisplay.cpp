#include <sstream>
#include <string>

#include "FPSDisplay.hpp"
#include "SDLCore.hpp"

FPSDisplay::FPSDisplay(int update_time) : HUDElement()
{
	point_f p;
	p.x = 0;
	p.y = 0;
	FPSDisplay(&p, update_time);
}

FPSDisplay::FPSDisplay(point_f *position, int update_time) : HUDElement(position)
{
	this->update_time = update_time;
	std::string font_name = "/home/chris/Documents/code/2D-game-engine/assets/font/FUTRFW.TTF";
	font = TTF_OpenFont(font_name.c_str(), 14);
	if (font == nullptr)
	{
		printTTFError();
	}
}

void FPSDisplay::update(float delta_time)
{
	frame_counter++;
	elapsed_time += delta_time;
	if (elapsed_time >= update_time)
	{
		fps = elapsed_time / frame_counter;
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
	std::stringstream fps_stream;
	fps_stream << fps;

	SDL_Surface* fps_surface = TTF_RenderText_Solid(font, fps_stream.str().c_str(), {80, 255, 0});
	if (fps_surface == nullptr)
	{
		printTTFError();
	}
	Rect()->w = fps_surface->w;
	Rect()->h = fps_surface->h; 
	texture = SDL_CreateTextureFromSurface(renderer, fps_surface);

	SDL_FreeSurface(fps_surface);
	SDL_RenderCopy(renderer, texture, nullptr, Rect());
}