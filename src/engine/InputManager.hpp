#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <functional>
#include <vector>
#include <string>

#include "Entity.hpp"
#include "EngineCore.hpp"
#include "geometry.hpp"

namespace Input
{
	typedef std::function<void(void*)> Callback;
	typedef uint32_t HandlerID;
	typedef struct
	{
		SDL_Keycode key;
		Input::Callback callback;
		void* arg;
	} Handler;

	void init();
	void unbind(Input::Handler* handler);
	void bind(Input::Handler* handler);
	void destroy();
}

#endif