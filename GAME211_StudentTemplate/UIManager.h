#pragma once
#include "Menu.h"
using namespace ui;


/// <summary>
///	This class is lowkey optional. this just depends on how we want to make our menus. is it an overlay? or is it a separate scene?
///	this needs to be discussed
/// </summary>
		
namespace menu {
	class UIManager : private Button {
	public:
			///	Constructor
		UIManager
		(SDL_Renderer* buttonRenderer) : buttonRenderer(buttonRenderer) { }


		void AddButton(Button &button) {
			buttons.push_back(&button);
		}


		void HandleButtonEvents(SDL_Event& event) {
			for (Button* button : buttons) {
				button->HandleEvent(event);
			}
		}


		void UpdateButtons(float deltaTime){
			for (Button* button : buttons) {
				button->Update(deltaTime);
			}
		}


		bool RenderMenu(bool render) {
			if (!render) { return false; }
	
			for (Button* button : buttons) {
				if (button->Render()) { button->setPosition(); }
			} buttons.clear();





		}


	private:
		SDL_Renderer* buttonRenderer;
		std::vector<Button*> buttons;
	};

}