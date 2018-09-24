#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <functional>
#include "EngineCore.hpp"
#include "geometry.hpp"


namespace Input
{
	typedef std::function<void (SDL_Event *)> Callback;
	typedef uint32_t CallbackID;

	typedef enum
	{
		DOWN,
		HOLD,
		UP
	} Type;

	void handle_input_event(SDL_Event *event);
	void update();

	//keyboard input callbacks
	CallbackID bind_key_down(SDL_Scancode key, Callback *callback_fn);
	CallbackID bind_key_hold(SDL_Scancode key, Callback *callback_fn);
	CallbackID bind_key_up(SDL_Scancode key, Callback *callback_fn);

	//mouse input callbacks
	CallbackID bind_mouse_move(Callback *callback_fn);
	CallbackID bind_button_down(uint8_t button, Callback *callback_fn);
	CallbackID bind_button_hold(uint8_t button, Callback *callback_fn);
	CallbackID bind_button_up(uint8_t button, Callback *callback_fn);

	Callback *unbind(CallbackID id);
}

#endif