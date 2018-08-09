#include "SnekGame.hpp"
#include "FirstLevel.hpp"

int main(int argc, char *args[])
{
	SnekGame game;

	if (game.init_window())
	{
		FirstLevel *first_level = new FirstLevel();
		game.start_game(first_level);
	}
	else
	{
		return -1;
	}
	game.close_window();

	return 0;
}

bool SnekGame::start_game(IScene *scene)
{
	SDL_ShowCursor(SDL_DISABLE);

	return Game::start_game(scene);
}
