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


	scene3Button = new Button(Font{ "diana land", 100 });
	scene3Button->textColour = SDL_COLOR_EMERALD_GREEN << SDL_White50;
	scene3Button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT); scene3Button->offsetPosition(-300);
	allButtons.emplace_back(scene3Button);


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


	return true;
}

void Scene3::OnDestroy() {
	for (auto* button : allButtons) {
		delete button;
	}
}

void Scene3::Update(const float deltaTime) {
	// Update player
}

void Scene3::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);


	for(auto* button : allButtons) { button->Render(renderer); }


	// render the player

	SDL_RenderPresent(renderer);
}

void Scene3::HandleEvents(const SDL_Event& event)
{
	for (auto* button : allButtons) { button->HandleEvents(event); }
}
