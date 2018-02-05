#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <functional>
#include "GameCore.hpp"
#include "rectd.hpp"

namespace Input
{
	typedef std::function<void (SDL_Event *)> callback;

	void handle_input_event(SDL_Event *event);
	void update();

	uint32_t bind_key_down(SDL_Scancode key, callback *fn);
	uint32_t bind_key_hold(SDL_Scancode key, callback *fn);
	uint32_t bind_key_up(SDL_Scancode key, callback *fn);

	uint32_t bind_mouse_move(callback *fn);
	uint32_t bind_mouse_button_down(uint8_t button, callback *fn);
	uint32_t bind_mouse_button_hold(uint8_t button, callback *fn);
	uint32_t bind_mouse_button_up(uint8_t button, callback *fn);

	callback *unbind(uint32_t id);
}

#endif