#include <sstream>

#include "FPSDisplay.hpp"
#include "SDLCore.hpp"
#include "AssetManager.hpp"

FPSDisplay::FPSDisplay(point_f *position, int update_time) : HUDElement(position)
{
	this->update_time = update_time;
	AssetManager::font(&FONT_NAME, FONT_SIZE, &font);
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
	std::stringstream fps_stream;
	fps_stream << fps;
	std::string fps_string = fps_stream.str();

	SDL_Surface *fps_surface = TTF_RenderText_Solid(font, fps_string.c_str(), {255, 255, 255});
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