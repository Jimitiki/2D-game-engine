#include "PawngGame.hpp"

int main(int argc, char *args[])
{
	PawngGame game;

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

bool PawngGame::start_game()
{
	SDL_ShowCursor(SDL_DISABLE);
	return Game::start_game();
}
