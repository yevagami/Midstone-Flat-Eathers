#pragma once
#include "GameManager.h"
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
		//UIManager(SDL_Renderer* buttonRenderer_) : buttonRenderer(buttonRenderer_) {}

		~UIManager() { DeleteAllButtons(); }

		void buttonPreset1() {
			//Button* button1 = new Button(buttonRenderer, Font{ "testing", 45, fontMap.at("comic sans") });
			//Button* button2 = new Button(buttonRenderer, Font{ "my testing <3", 45, fontMap.at("comic sans") });

			/*AddButtonToScene(*button1);
			AddButtonToScene(*button2);*/

			for(auto button : buttons) {
				button->generateHitbox();
				button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
				button->offsetPosition(-300);

			}


		}


		//void AddButtonsToScene(const vector<Button*>& listOfButtons_) {
		//	for (Button* &button : listOfButtons_) {
		//		buttons.emplace_back(button);
		//	}
		//}


		void AddButtonToScene(Button &button_) {
			buttons.emplace_back(&button_);
		}

		void DeleteAllButtons() {
			for (auto* button : buttons) {
				delete button;
			}

		}


		void HandleButtonEvents(const SDL_Event& event_) const {
			for (Button* button : buttons) {
				button->HandleEvents(event_);
			}
		}


		void UpdateButtons(float deltaTime){
			for (Button* button : buttons) {
				button->Update(deltaTime);
			}
		}


		bool RenderMenu(SDL_Renderer* renderer_, bool render_ = true) {
			if (!render_) { return false; }

			for (Button* button : buttons) {button->Render(renderer_);}
			return true;

		}


	private:
		SDL_Renderer* buttonRenderer;
		std::vector<Button*> buttons;
	};

}