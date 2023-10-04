#pragma once
#include <iostream>
#include <SDL.h>

namespace keybinds {
	struct keys {
	protected:
		static enum class SDLEventType {
			KeyDown,
			KeyUp,
			MouseMotion,
			MouseButtonDown,
			MouseButtonUp,
			Quit,
		};

		static enum class Key {
			A, B, C, D, E, F, G, H, I, J, K, L, M,
			N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
			Space, Enter, Escape, Backspace, Tab, Shift, Ctrl, Alt,
			Left, Right, Up, Down,
		};

	public:
		void HandleEvents(const SDL_Event& event) {
			switch (static_cast<SDLEventType>(event.type)) {
			case SDLEventType::KeyDown:
				switch (static_cast<Key>(event.key.keysym.sym)) {
				case Key::Escape:
					//	flag to exit the main loop
					break;
				case Key::P:
					std::cout << "testing\n";
					break;
				}
			break; 

		}
		}



	};
}