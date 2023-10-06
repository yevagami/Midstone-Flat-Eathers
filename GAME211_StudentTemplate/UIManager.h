#pragma once
#include "Menu.h"


namespace menu {
	class UIManager : public ui::Button {
	public:
			///	Constructor
		UIManager
		(SDL_Renderer* buttonRenderer) : buttonRenderer(buttonRenderer) { }

		void AddButton(Button &button) {
			buttons.push_back(&button);
		}

		void HandleButtonEvents(SDL_Event& event) {
			for (ui::Button* button : buttons) {
				button->HandleEvent(event);
			}
		}

		void UpdateButtons(float deltaTime){
			for (ui::Button* button : buttons) {
				button->Update(deltaTime);
			}
		}

	private:
		SDL_Renderer* buttonRenderer;
		std::vector<Button*> buttons;
	};

}