#include "Scene4.h"
#include "PrettyPrinting.h"

using namespace ui;




// See notes about this constructor in Scene1.h.
Scene4::Scene4(SDL_Window* sdlWindow_, GameManager* game_) {

	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1600.0f;
	yAxis = 900.0f;


	scene4Button = new Button(Font{ "MY land >:)", 100 , fontMap.at("gothic")});
	scene4Button->textColour = SDL_COLOR_DARK_RED << SDL_White50;
	scene4Button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT); scene4Button->offsetPosition(-300);
	allButtons.emplace_back(scene4Button);


}

Scene4::~Scene4() = default;

bool Scene4::OnCreate() {
#pragma region SDL Window Stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
#pragma endregion
	name = "scene4";


	block = new Body();
	block->setPos(Vec3(xAxis * 0.5f + 200.0f, yAxis * 0.5f, 0.0f));
	block->setImage(IMG_Load("Textures/blue_block.jpg"));
	block->setTexture(SDL_CreateTextureFromSurface(renderer, block->getImage()));
	block->LoadHitbox(
		225.0f,
		225.0f
	);


	game->getPlayer()->LoadHitbox(
		542.0f * 0.1f,
		571.0f * 0.1f
	);





	return true;
}

void Scene4::OnDestroy() {
	for (auto* button : allButtons) {
		delete button;
	}
}

void Scene4::Update(const float deltaTime) {
	//camera position update
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);

	float left = game->getPlayer()->getPos().x - xAxis / 2.0f;
	float right = game->getPlayer()->getPos().x + xAxis / 2.0f;
	float top = game->getPlayer()->getPos().y - yAxis / 2.0f;
	float bottom = game->getPlayer()->getPos().y + yAxis / 2.0f;

	Matrix4 ortho = MMath::orthographic(left, right, top, bottom, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;


	if (game->getPlayer()->getHitbox().collisionCheck(block->getHitbox())) {
		game->getPlayer()->CollisionResponse(deltaTime, block);
		std::cout << "Collided\n";
	};


	block->Update(deltaTime);
	game->getPlayer()->Update(deltaTime);


	block->UpdateHitbox(projectionMatrix);
	game->getPlayer()->UpdateHitbox(projectionMatrix);
}

void Scene4::Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	for (auto* button : allButtons) {
		button->Render(renderer);
	}


	block->Render(renderer, projectionMatrix);
	game->RenderPlayer(0.1f);

	game->getPlayer()->RenderHitbox(renderer, projectionMatrix, 0.1f);
	block->RenderHitbox(renderer, projectionMatrix, 1.0f);






	SDL_RenderPresent(renderer);
}

void Scene4::HandleEvents(const SDL_Event& event)
{
	for (auto* button : allButtons) { button->HandleEvents(event); }


	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

}
