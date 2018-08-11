#ifndef FIRSTLEVEL_H_
#define FIRSTLEVEL_H_

#include "../engine/IScene.hpp"

#include <vector>

#include "../engine/Entity.hpp"
#include "../engine/InputManager.hpp"

class FirstLevel : public IScene
{
public:
	void load() {}

	std::vector<Entity *> *init();

	void destroy() {};

	void unload() {};
private:
	std::vector<Entity *> *entities;
};

#endif
