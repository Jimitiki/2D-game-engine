#include "../engine/Game.hpp"
#include "../engine/IScene.hpp"

class SnekGame : public Game
{
public:
	bool start_game(IScene *scene);
};