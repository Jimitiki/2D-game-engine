#include <sstream>
#include <unordered_map>
#include "AssetManager.hpp"

namespace AssetManager
{
	namespace
	{
		std::string FONT_DIR = "../assets/font/";
		std::string IMAGE_DIR = "../assets/img/";
		std::unordered_map<std::string, TTF_Font *> fonts;
		std::unordered_map<std::string, SDL_Surface *> surfaces;
	}

	bool font(std::string *font_name, int font_size, TTF_Font **font)
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
				printTTFError();
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

	bool surface(std::string *surface_name, SDL_Surface **surface)
	{
		*surface = nullptr; 
		return false;
	}
}