#ifndef CURSOR_HPP_
#define CURSOR_HPP_

class Cursor
{
	public:
		Cursor(std::string image_name);
		void update(int delta_time);
		void draw(SDL_Renderer *renderer);

	private:
		
}