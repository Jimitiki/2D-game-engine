#include <sstream>
#include <unordered_map>
#include "AssetManager.hpp"

namespace Asset
{
	namespace
	{

		#ifdef __linux__
		std::string FONT_DIR = "../assets/font/";
		std::string IMAGE_DIR = "../assets/img/";
		#endif

		#ifdef _WIN32
		std::string FONT_DIR = "assets/font/";
		std::string IMAGE_DIR = "assets/img/";
		#endif	

		std::unordered_map<std::string, TTF_Font *> fonts;
		std::unordered_map<std::string, SDL_Surface *> images;
	}
}
	
bool Asset::font(std::string *font_name, int font_size, TTF_Font **font)
{
	std::stringstream key_stream;
	key_stream << *font_name << font_size;

	//uniquely tag each font name with the file name & the font size
	std::string key = key_stream.str();
	
	std::unordered_map<std::string, TTF_Font *>::iterator result = fonts.find(key);
	if (result == fonts.end())
	{
		std::string font_file = FONT_DIR + *font_name;
		*font = TTF_OpenFont(font_file.c_str(), font_size);
		if (*font == nullptr)
		{
			print_ttf_error();
			throw std::exception();
			return false;
		}
		std::pair<std::string, TTF_Font *> new_font(key, *font);
		fonts.insert(new_font);
	}
	else
	{
		*font = result->second;
	}
	return true;
}

bool Asset::image(std::string *image_name, SDL_Surface **surface)
{
	std::unordered_map<std::string, SDL_Surface *>::iterator result = images.find(*image_name);
	if (result == images.end())
	{
		std::string image_file = IMAGE_DIR + *image_name;
		*surface = IMG_Load(image_file.c_str());
		if (*surface == nullptr)
		{
			print_img_error();
			throw std::exception();
			return false;
		}
		std::pair<std::string, SDL_Surface *> new_image(*image_name, *surface);
		images.insert(new_image);
	}
	else
	{
		*surface = result->second;
	}
	return false;
}

void Asset::unload_all()
{
	for (auto iterator : fonts)
	{
		TTF_CloseFont(iterator.second);
	}
	for (auto iterator : images)
	{
		SDL_FreeSurface(iterator.second);
	}
}
