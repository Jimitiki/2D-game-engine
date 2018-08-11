#include "../engine/Game.hpp"
#include "../engine/IScene.hpp"
#include "../engine/Cursor.hpp"

class SnekGame : public Game
{
public:
	bool start_game(IScene *scene);
};