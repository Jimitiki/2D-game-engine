#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <functional>
#include <vector>

#include "Entity.hpp"
#include "EngineCore.hpp"
#include "geometry.hpp"


namespace Input
{
	typedef enum
	{
		UP,
		DOWN,
		HOLD
	} Type;
	typedef std::function<void(void*)> Callback;
	typedef uint32_t HandlerID;
	typedef struct
	{
		Input::Type type;
		SDL_Keycode key;
		Input::Callback callback;
		void* arg;
	} Handler;

	void init();
	//void update(int delta_t);
	void unbind(Input::Handler* handler);
	void bind(Input::Handler* handler);
	void destroy();
}

#endif