#pragma once
#include <iostream>
#include <SDL.h>

namespace keybinds {
	struct keys {
	protected:
		static enum class SDLEventType {
			Quit,
			KeyDown,
			KeyUp,
			MouseMotion,
			MouseButtonDown,
			MouseButtonUp,
		};

		static enum class Key {
			A, B, C, D, E, F, G, H, I, J, K, L, M,
			N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
			Space, Enter, Escape, Backspace, Tab, Shift, Ctrl, Alt,
			Left, Right, Up, Down,
		};

	public:
		void HandleEvents(const SDL_Event event) {
			switch (static_cast<SDLEventType>(event.type)) {
			case SDLEventType::KeyDown:
#pragma region keyDown
				switch (static_cast<Key>(event.key.keysym.sym)) {
				case Key::Escape:
					//	flag to exit the main loop
					break;
				case Key::P:
					std::cout << "testing\n";
					break;
				}
#pragma endregion
			break;

		}
		}



	};
}