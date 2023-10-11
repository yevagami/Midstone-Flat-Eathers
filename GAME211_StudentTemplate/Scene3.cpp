#include "Scene3.h"
#include "PrettyPrinting.h"

using namespace ui;




// See notes about this constructor in Scene1.h.
Scene3::Scene3(SDL_Window* sdlWindow_, GameManager* game_) {

	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene3::~Scene3() = default;

bool Scene3::OnCreate() {
#pragma region SDL Window Stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
#pragma endregion
	name = "scene3";

	Button* scene3Button = new _debugbutton; // m a c r o


	allButtons.emplace_back(scene3Button);

	return true;
}

void Scene3::OnDestroy() {
	for (auto* button : allButtons) {
		delete button;
	}
}

void Scene3::Update(const float deltaTime) {
	// Update player
	game->getPlayer()->Update(deltaTime);


}

void Scene3::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


	for(auto* button : allButtons) { button->Render(renderer); }


	// render the player
	game->RenderPlayer(0.1f);

	SDL_RenderPresent(renderer);
}

void Scene3::HandleEvents(const SDL_Event& event)
{
	//for (auto* button : allButtons) { button->HandleEvents(event); }


	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

}
