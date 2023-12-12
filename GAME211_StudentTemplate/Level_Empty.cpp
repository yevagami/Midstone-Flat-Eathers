#include "Level_MainMenu.h"


bool Level_MainMenu::OnCreate(){




	return true;
}


void Level_MainMenu::OnDestroy(){





	//Destroys everything except the player
	for (Body* body : levelBodies) {
		if (body->type == body->PLAYER) {
			body = nullptr;
			continue;
		}
		body->OnDestroy();
		delete body;
	}

	levelBodies.clear();
}


void Level_MainMenu::Update(const float time_){



}

void Level_MainMenu::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_){


}

void Level_MainMenu::HandleEvents(const SDL_Event& event_){



}
