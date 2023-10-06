#pragma once
#include "Menu.h"


namespace ui {
	class UIManager : public Button {
	public:
			///	Constructor
		UIManager(
			SDL_Renderer* buttonRenderer)
			: buttonRenderer(buttonRenderer) 
		{
			
		}


		void AddButton(SDL_Rect rect, SDL_Color bgCol, const char* font, int fontSize) {
			//Button button(buttonRenderer, rect, bgCol, font, fontSize);
			//buttons.push_back(button);
		}

		void HandleButtonEvents(SDL_Event& event) {
			for (ui::Button &button : buttons) {
				button.HandleEvent(event);
			}
		}

		void UpdateButtons(float deltaTime){
			for (ui::Button& button : buttons) {
				button.Update(deltaTime);
			}
		}

	private:
		SDL_Renderer* buttonRenderer;
		std::vector<Button> buttons;
	};

}