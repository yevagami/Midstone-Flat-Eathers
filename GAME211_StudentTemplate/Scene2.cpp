#include "Scene2.h"
using namespace ui;


Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1600.0f;
	yAxis = 900.0f;

	scene2Button = new Button(Font{ "Adriel World", 100 });
	scene2Button->textColour = SDL_COLOR_DEEP_PINK << SDL_White50;
	scene2Button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT); scene2Button->offsetPosition(-300);
	allButtons.emplace_back(scene2Button);

}

Scene2::~Scene2(){
}

bool Scene2::OnCreate(){
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	name = "scene2";


	//Create the body
	block = new Body();
	block->setPos(Vec3(xAxis * 0.5f + 200.0f, yAxis * 0.5f, 0.0f));
	block->setImage(IMG_Load("Textures/blue_block.jpg"));
	block->setTexture(SDL_CreateTextureFromSurface(renderer, block->getImage()));
	block->LoadHitbox(
		225.0f,
		225.0f
	);
	block->setParentScene(this);

	//Load the body's hitbox
	game->getPlayer()->LoadHitbox(
		542.0f * 0.1f,
		571.0f * 0.1f
	);
	game->getPlayer()->setParentScene(this);

	return true;
}

void Scene2::OnDestroy() {
	for (auto* button : allButtons) {
		delete button;
	}
	delete block;
}

void Scene2::Update(const float time){
	//move the camera  update
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);

	float left = game->getPlayer()->getPos().x - xAxis / 2.0f;
	float right = game->getPlayer()->getPos().x + xAxis / 2.0f;
	float top = game->getPlayer()->getPos().y - yAxis / 2.0f;
	float bottom = game->getPlayer()->getPos().y + yAxis / 2.0f;

	Matrix4 ortho = MMath::orthographic(left, right, top, bottom, 0.0f, 1.0f);//
	projectionMatrix = ndc * ortho;

	//Check for collision
	if (game->getPlayer()->getHitbox().collisionCheck(block->getHitbox())) {
		game->getPlayer()->CollisionResponse(time, block);
		std::cout << "Collided\n";
	};

	//Update the body
	block->Update(time);
	game->getPlayer()->Update(time);
}

void Scene2::Render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	block->Render(renderer, projectionMatrix);
	game->RenderPlayer(0.1f);

	game->getPlayer()->RenderHitbox(renderer, 0.1f);
	block->RenderHitbox(renderer, 1.0f);


	for(auto* button : allButtons) {
		button->Render(renderer);
	}


	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event){
	game->getPlayer()->HandleEvents(event);
}
