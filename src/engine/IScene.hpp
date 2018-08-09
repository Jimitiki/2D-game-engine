#ifndef ISCENE_H_
#define ISCENE_H_

#include "Entity.hpp"

class IScene
{
public:
	virtual void load() = 0;

	virtual std::vector<Entity *> *init() = 0;

	virtual void destroy() = 0;

	virtual void unload() = 0;
};

#endif