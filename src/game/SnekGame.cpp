#include "SnekGame.hpp"

int main(int argc, char *args[])
{
	SnekGame game;

	if (game.init_window())
	{
		game.start_game();
	}
	else
	{
		return -1;
	}
	game.close_window();

	return 0;
}

bool SnekGame::start_game()
{
	SDL_ShowCursor(SDL_DISABLE);
	return Game::start_game();
}
